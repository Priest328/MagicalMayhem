// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponAttackStrategy.generated.h"



UENUM(BlueprintType)
enum class EShootingStrategy : uint8
{
	ProjectileShootStrategy,
	RayCastShootStrategy
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponAttackStrategy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
//DECLARE_EVENT(IStrategyBase, FUpdateAmmoAmount)

class MAGICALMAYHEM_API IWeaponAttackStrategy 
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual EShootingStrategy GetType() = 0;
	
	UFUNCTION()
	virtual void Shoot(UWeaponComponent* WeaponComponent) = 0;

	UFUNCTION()
	virtual FString GetMessage() = 0;
};
