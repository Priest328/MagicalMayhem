// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicalMayhem/GameLogicAsset.h"
#include "MagicalMayhem/HealthComponent.h"
#include "MagicalMayhem/Widgets/HealthAmmoBarWidget.h"
#include "MagicalMayhem/Widgets/MissionWidget.h"
#include "MagicalMayhem/WeaponLogic/SpawnProjectileComp.h"
#include "MagicalMayhem/WeaponLogic/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/KillZVolume.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/SpringArmComponent.h"
#include "MagicalMayhem/Widgets/StrategyWidget.h"
#include "MM_Character.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimDoubleJumpUpdate);

UCLASS()
class MAGICALMAYHEM_API AMM_Character : public ACharacter
{
	GENERATED_BODY()

public:
	AMM_Character();

	UFUNCTION()
	void ToShoot();

	UFUNCTION()
	void UpdateObjectivesProgress(AActor* DestroyedActor);

	UFUNCTION()
	void HandleMapChange();

	UFUNCTION()
	void UpdateHealthWidget();

	UFUNCTION()
	void UpdateWeaponWidgets();

	UFUNCTION()
	void UpdateMissionWidget(FString& MisionText);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;

	virtual void FellOutOfWorld(const UDamageType& dmgType) override;

	void TurnOffWidgets();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FAnimDoubleJumpUpdate UpdateAnimEvent;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp = nullptr;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// USpawnProjectileComp* SpawnProjectileComp = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WeaponComponent")
	UWeaponComponent* WeaponComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Assets ")
	TArray<UGameLogicAsset*> GameLogicAssets;

	UPROPERTY(EditAnywhere, Category = "Properties")
	UHealthComponent* HealthComp = nullptr;


	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UHealthAmmoBarWidget> UserHealthAmmoWidget = nullptr;

	UPROPERTY()
	UHealthAmmoBarWidget* HealthAmmoWidget = nullptr;


	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UMissionWidget> UserMissionWidget = nullptr;

	UPROPERTY()
	UMissionWidget* MissionWidget = nullptr;


	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UStrategyWidget> UserStrategyWidget = nullptr;

	UPROPERTY()
	UStrategyWidget* StrategyWidget = nullptr;
};
