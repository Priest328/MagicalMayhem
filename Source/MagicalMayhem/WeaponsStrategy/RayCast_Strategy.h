// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicalMayhem/WeaponsStrategy/WeaponAttackStrategy.h"
//#include "Task16/WeaponLogic/WeaponComponent.h"

#include "RayCast_Strategy.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICALMAYHEM_API URayCast_Strategy : public UPrimaryDataAsset, public IWeaponAttackStrategy
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URayCast_Strategy();
	
	// virtual EShootingStrategy GetShootingStrategy() override;
	//
	// virtual void ToShoot() override;

	 UFUNCTION()
	 virtual EShootingStrategy GetType() override;

	 UFUNCTION()
	 virtual  void Shoot(UWeaponComponent* WeaponComponent) override;

	UFUNCTION()
	virtual FString GetMessage() override;
	//virtual void UpdateAmmoAmount() override;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float MaxRayCastLength = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
	FString Message;
};
