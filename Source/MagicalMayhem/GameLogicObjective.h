// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "MM_GameMode.h"
#include "GameLogicObjective.generated.h"

/**
 * 
 */

UCLASS()
class MAGICALMAYHEM_API UGameLogicObjective : public UObject
{
	GENERATED_BODY()

public:
	UGameLogicObjective();
	

	UFUNCTION()
 	bool DecreaseAmount();
//
// 	void SetAmountOfObjects(int32 Amount);
// 	int32 GetAmountOfObjects();
//
// 	void TimerFunction();
//
// private:
// 	UPROPERTY()
// 	UActorHealthComponent* HealthComponent = nullptr;
//
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AmountOfObjectsToDestroy")
	int32 AmountOfObjects = 1;
//
// public:
// 	FTimerHandle TimerHandle;
//
// 	float TimerTracker = 3;
	

};
