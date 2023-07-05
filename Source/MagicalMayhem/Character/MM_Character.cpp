// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MagicalMayhem/MM_PlayerController.h"
#include "MagicalMayhem/Widgets/HealthAmmoBarWidget.h"
#include "MagicalMayhem/HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

AMM_Character::AMM_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(GetRootComponent());

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	// SpawnProjectileComp = CreateDefaultSubobject<USpawnProjectileComp>("ProjectComp");
	// SpawnProjectileComp->SetupAttachment(GetRootComponent());

    PawnNoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitterComp"));

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");
	WeaponComponent->SetupAttachment(SpringArmComp);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
}


void AMM_Character::BeginPlay()
{
	Super::BeginPlay();
	for (auto Asset : GameLogicAssets)
	{
		UE_LOG(LogTemp, Warning, TEXT("AddDynemic"));
		
		Asset->OnCompleted.AddDynamic(this, &AMM_Character::HandleMapChange);
	}
	
	if (UserHealthAmmoWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("1"));
		HealthAmmoWidget = CreateWidget<UHealthAmmoBarWidget>(UGameplayStatics::GetPlayerController(GetWorld(),0), UserHealthAmmoWidget);
		if (HealthAmmoWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("2"));
			HealthAmmoWidget->SetHealth(HealthComp->Health,HealthComp->MaxHealth);
			HealthAmmoWidget->SetAmmo(WeaponComponent->CurrentAmmoAmount,WeaponComponent->MaxAmmoAmount);
			HealthAmmoWidget->AddToViewport();
		}
	}
	
	if (UserMissionWidget)
	{
		MissionWidget = CreateWidget<UMissionWidget>(UGameplayStatics::GetPlayerController(GetWorld(),0), UserMissionWidget);

		if(MissionWidget)
		{
			MissionWidget->AddToViewport();
		}
	}
	
    if (UserStrategyWidget)
    {
	    StrategyWidget = CreateWidget<UStrategyWidget>(UGameplayStatics::GetPlayerController(GetWorld(),0), UserStrategyWidget);
    	if(StrategyWidget)
    	{
    		StrategyWidget->AddToViewport();
    		StrategyWidget->ChangeStrategy("ProjectileStrategy");
    	}
    }
	
	HealthComp->HealthWidget.AddUObject(this, &AMM_Character::UpdateHealthWidget);
    WeaponComponent->UpdateWeaponWidget.AddUObject(this, &AMM_Character::UpdateWeaponWidgets);

	
	for (auto Asset : GameLogicAssets)
	{
		MissionWidget->SetMission(Asset->MissionDescription); 
		Asset->OnChangeMisionWidget.AddUObject(this, &AMM_Character::UpdateMissionWidget);
	}

	
}

void AMM_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMM_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMM_Character::ToShoot()
{
    WeaponComponent->WeaponToShoot();
}

void AMM_Character::UpdateObjectivesProgress(AActor* DestroyedActor)
{
	for (auto Asset : GameLogicAssets)
	{
		Asset->ApplyObjectDeath(DestroyedActor);
	}
}

void AMM_Character::HandleMapChange()
{
	if (AMM_PlayerController* CustomPlayerController = Cast<AMM_PlayerController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		CustomPlayerController->OnMapChange();
	}
}

void AMM_Character::UpdateHealthWidget()
{
	HealthAmmoWidget->SetHealth(HealthComp->Health,HealthComp->MaxHealth);
}

float AMM_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HealthComp->ApplyDamage(DamageAmount);
	return DamageAmount;
}

void AMM_Character::UpdateMissionWidget(FString& MissionText)
{
	MissionWidget->SetMission(MissionText);
}

void AMM_Character::UpdateWeaponWidgets()
{
	HealthAmmoWidget->SetAmmo(WeaponComponent->CurrentAmmoAmount,WeaponComponent->MaxAmmoAmount);

	if(WeaponComponent->CurrentStrategy->GetType() == EShootingStrategy::ProjectileShootStrategy)
	{
		StrategyWidget->ChangeStrategy("ProjectileStrategy");
	}
	if(WeaponComponent->CurrentStrategy->GetType() == EShootingStrategy::RayCastShootStrategy)
	{
		StrategyWidget->ChangeStrategy("RayCastStrategy");
	}
}

void AMM_Character::FellOutOfWorld(const UDamageType& dmgType)
{


	DetachFromControllerPendingDestroy();

	// Hide and disable the current pawn
	TurnOff();
	SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
    TurnOffWidgets();
	GetWorld()->GetAuthGameMode()->RestartPlayer(UGameplayStatics::GetPlayerController(GetWorld(),0));
}

void AMM_Character::TurnOffWidgets()
{
	// MissionWidget->RemoveFromViewport();
	// HealthAmmoWidget->RemoveFromViewport();
	// StrategyWidget->RemoveFromViewport();
}






