// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MM_GameMode.h"
#include "GameFramework/PlayerController.h"
#include "MenuLogic/GameMenuUserWidget.h"
#include "MM_PlayerController.generated.h"


UCLASS()
class MAGICALMAYHEM_API AMM_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

    AMM_PlayerController();

	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void SetupInputComponent() override;
	
	UFUNCTION()
	void TimerFunction();
	
	UFUNCTION()
	void ToShoot();

	UFUNCTION()
	void ToReload();
	
	UFUNCTION()
	void SetStrategy_1();
	
	UFUNCTION()
	void SetStrategy_2();

	UFUNCTION()
    void MouseWheelStrategy(float value);
	
	UFUNCTION()
    void OnMapChange();

	UFUNCTION()
	void QuitToMainMenu();

	UFUNCTION()
	void ResumeGame();
	
	UFUNCTION()
	void OnPause();
	
private:

	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override;
	UFUNCTION()
	void TurnAtRate(float Value);

	UFUNCTION()
	void LookUpAtRate(float Value);
	
	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void Jump();

	UFUNCTION()
	void Crouch();
	UFUNCTION()
	void Sprint();

public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "SpawnUnits")
    TSubclassOf<AActor> ActorToSpawn = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseTurnRate = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseLookUpAtRate = 50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UGameMenuUserWidget> UserGameMenuWidget = nullptr;

	UPROPERTY()
	UGameMenuUserWidget* GameMenuWidget = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 ObjectsToDestroy = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 600; // when sprint : WalkSpeed * 2
	                       // when crouch : WalkSpeed / 2
	
private:
	bool bIsInMenu = false;
	
	FTimerHandle TimerHandle;
	
	int TimerTracker = 3;
	
	//Checker for max amount of jump in air, can be changed to increase max amount of jumps in air.
	// For double jump.
	const int8 MaxJumpCount = 2; 

	int8 CurrentJumpCount = 0;

	bool bIsSprint = false;
	
	UPROPERTY()
	AMM_Character* mm_Character = nullptr;
};
