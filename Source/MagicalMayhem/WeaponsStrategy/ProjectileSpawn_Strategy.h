// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicalMayhem/WeaponsStrategy/WeaponAttackStrategy.h"
#include "Components/SceneComponent.h"
//#include "Task16/WeaponLogic/WeaponComponent.h"
#include "ProjectileSpawn_Strategy.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MAGICALMAYHEM_API UProjectileSpawn_Strategy : public UPrimaryDataAsset, public IWeaponAttackStrategy
{
	GENERATED_BODY()

public:
	UProjectileSpawn_Strategy();
	
	// virtual EShootingStrategy GetShootingStrategy() override;
	//
	// virtual void ToShoot() override;
	UFUNCTION()
	virtual EShootingStrategy GetType() override;

	UFUNCTION()
	virtual void Shoot(UWeaponComponent* WeaponComponent) override;

	UFUNCTION()
	virtual FString GetMessage() override;
	//virtual void UpdateAmmoAmount() override;


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> ActorToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
	FString Message;
};
