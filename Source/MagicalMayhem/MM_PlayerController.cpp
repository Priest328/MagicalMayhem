// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_PlayerController.h"

#include "Character/MM_Character.h"

#include "Components/Button.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AMM_PlayerController::AMM_PlayerController()
{
}

void AMM_PlayerController::BeginPlay()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;
	SetInputMode(FInputModeGameOnly());
	if (UserGameMenuWidget)
	{
		GameMenuWidget = CreateWidget<UGameMenuUserWidget>(GetWorld(), UserGameMenuWidget);
		if (GameMenuWidget)
		{
			GameMenuWidget->ResumeGameButton->OnClicked.AddDynamic(this, &AMM_PlayerController::ResumeGame);
			GameMenuWidget->QuitToMainMenuButton->OnClicked.AddDynamic(this, &AMM_PlayerController::QuitToMainMenu);
		}
	}
	mm_Character = Cast<AMM_Character>(GetCharacter());
	if (mm_Character)
	{
		mm_Character->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}


void AMM_PlayerController::SetupInputComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("SetupInputComponent used"));

	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("MoveForward"), this, &AMM_PlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AMM_PlayerController::MoveRight);

	InputComponent->BindAxis(TEXT("Turn"), this, &AMM_PlayerController::TurnAtRate);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AMM_PlayerController::LookUpAtRate);
	InputComponent->BindAxis(TEXT("MouseWheel"), this, &AMM_PlayerController::MouseWheelStrategy);

	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMM_PlayerController::Jump);
	InputComponent->BindAction(TEXT("ToShoot"), IE_Pressed, this, &AMM_PlayerController::ToShoot);

	InputComponent->BindAction(TEXT("ShootStrategy1"), IE_Pressed, this, &AMM_PlayerController::SetStrategy_1);
	InputComponent->BindAction(TEXT("ShootStrategy2"), IE_Pressed, this, &AMM_PlayerController::SetStrategy_2);

	InputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AMM_PlayerController::ToReload);

	InputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMM_PlayerController::Sprint);
	InputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMM_PlayerController::Sprint);

	InputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AMM_PlayerController::Crouch);
	InputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AMM_PlayerController::Crouch);
	
}

void AMM_PlayerController::MoveForward(float Value)
{
	//
	if (Value != 0.0f)
	{
		//UE_LOG(LogTemp,Warning,TEXT("MoveForward"));
		APawn* MyPawn = GetPawn();

		if (MyPawn)
		{
			const FRotator YawRotation(0, GetControlRotation().Yaw, 0);
			FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);

			MyPawn->AddMovementInput(Direction, Value);
		}
	}
}

void AMM_PlayerController::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		//UE_LOG(LogTemp,Warning,TEXT("MoveRight"));
		APawn* MyPawn = GetPawn();

		if (MyPawn)
		{
			const FRotator YawRotation(0, GetControlRotation().Yaw, 0);
			FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

			MyPawn->AddMovementInput(Direction, Value);
		}
	}
}

//
void AMM_PlayerController::Jump()
{
	if (mm_Character)
	{
		mm_Character->JumpMaxCount = MaxJumpCount;
		mm_Character->Jump();
		if (mm_Character->JumpCurrentCount == MaxJumpCount - 1)
		{
			mm_Character->UpdateAnimEvent.Broadcast();
		}
	}
}

void AMM_PlayerController::TurnAtRate(float Value)
{
	if (mm_Character)
	{
		mm_Character->AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMM_PlayerController::LookUpAtRate(float Value)
{
	if (mm_Character)
	{
		mm_Character->AddControllerPitchInput(Value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMM_PlayerController::ToShoot()
{
	if (mm_Character)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cast"));
		mm_Character->ToShoot();
	}
}

void AMM_PlayerController::OnMapChange()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMM_PlayerController::TimerFunction, 1, true);
	//UGameplayStatics::OpenLevel(GetWorld(), "NewMap");
}

void AMM_PlayerController::TimerFunction()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::FromInt(TimerTracker));
	TimerTracker -= 1;
	if (TimerTracker == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		UGameplayStatics::OpenLevel(GetWorld(), "NewMap");
	}
}

void AMM_PlayerController::SetStrategy_1()
{
	if (mm_Character)
	{
		mm_Character->WeaponComponent->ChangeShootStrategy(EShootingStrategy::ProjectileShootStrategy);
	}
}

void AMM_PlayerController::SetStrategy_2()
{
	if (mm_Character)
	{
		mm_Character->WeaponComponent->ChangeShootStrategy(EShootingStrategy::RayCastShootStrategy);
	}
}

void AMM_PlayerController::ToReload()
{
	if (mm_Character)
	{
		mm_Character->WeaponComponent->WeaponReload();
	}
}

void AMM_PlayerController::MouseWheelStrategy(float value)
{
	if (mm_Character)
	{
		if (value == 1)
		{
			mm_Character->WeaponComponent->Scroll(value);
		}

		if (value == -1)
		{
			mm_Character->WeaponComponent->Scroll(value);
		}
	}
}

void AMM_PlayerController::QuitToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu_Level");
}

void AMM_PlayerController::ResumeGame()
{
	bIsInMenu = true;
	OnPause();
}

bool AMM_PlayerController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	Super::InputKey(Key, EventType, AmountDepressed, bGamepad);

	if (Key == EKeys::Escape && EventType == EInputEvent::IE_Pressed)
	{
		OnPause();
	}
	return true;
}

void AMM_PlayerController::OnPause()
{
	if (GameMenuWidget)
	{
		if (bIsInMenu == false)
		{
			bIsInMenu = true;


			bShowMouseCursor = true;
			bEnableClickEvents = true;
			bEnableMouseOverEvents = true;
			GameMenuWidget->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			SetPause(true);
		}
		else if (bIsInMenu == true)
		{
			bIsInMenu = false;


			bShowMouseCursor = false;
			bEnableClickEvents = false;
			bEnableMouseOverEvents = false;
			GameMenuWidget->RemoveFromViewport();
			SetPause(false);
			SetInputMode(FInputModeGameOnly());
		}
	}
}

void AMM_PlayerController::Sprint()
{
	if (mm_Character)
	{
		if (bIsSprint == false)
		{
			mm_Character->GetCharacterMovement()->MaxWalkSpeed = mm_Character->GetCharacterMovement()->MaxWalkSpeed * 2;
			bIsSprint = true;
		}
		else
		{
			mm_Character->GetCharacterMovement()->MaxWalkSpeed = mm_Character->GetCharacterMovement()->MaxWalkSpeed / 2;
			bIsSprint = false;
		}
	}
}

void AMM_PlayerController::Crouch()
{
	if (mm_Character)
	{
		if (!mm_Character->GetCharacterMovement()->IsCrouching())
		{
			mm_Character->Crouch();
		}
		else
		{
			mm_Character->UnCrouch();
		}
	}
	
}
