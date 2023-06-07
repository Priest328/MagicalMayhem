// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"
#include "SpawnProjectileComp.generated.h"

UCLASS()
class MAGICALMAYHEM_API USpawnProjectileComp : public USceneComponent
{
	GENERATED_BODY()

public:
	USpawnProjectileComp();

	UFUNCTION()
	void SpawnUnit();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> ActorToSpawn;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	UStaticMeshComponent* SpawnPoint = nullptr;

	UPROPERTY(EditAnywhere, Category = "Impulse")
	float ImpulseStrength = 500;

	UPROPERTY(EditAnywhere, Category = "Impulse")
	bool bApplyImpulse = false;
};
