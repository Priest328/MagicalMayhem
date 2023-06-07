// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MagicalMayhem/WeaponsStrategy/WeaponAttackStrategy.h"
#include "WeaponComponent.generated.h"

DECLARE_EVENT(UWeaponComponent, FUpdateWeaponWidgets)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICALMAYHEM_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();
	
	UFUNCTION()
	void WeaponToShoot();

	UFUNCTION()
	void WeaponReload();

	UFUNCTION()
	void ChangeShootStrategy(EShootingStrategy Strategy);

	UFUNCTION()
	void Scroll(int8 value);
protected:
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
	TArray<UPrimaryDataAsset*> Strategies;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon Ammo")
	int MaxAmmoAmount = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon Ammo")
	int CurrentAmmoAmount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> ActorToSpawn;

	int16 CurrentStrategyIndex = 0;

	UPROPERTY(BlueprintReadOnly, Transient)
	TScriptInterface<IWeaponAttackStrategy> CurrentStrategy;
	// Error: ScriptInterface.h(160): [C2664] 'void FScriptInterface::SetObject(UObject *)': cannot convert argument 1 from 'UObjectType *' to 'UObject *'

	//IWeaponAttackStrategy* CurrentStrategy = nullptr;
	
	FUpdateWeaponWidgets UpdateWeaponWidget;
};
