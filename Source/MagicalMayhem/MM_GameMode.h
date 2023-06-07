// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Character/MM_Character.h"
#include "GameFramework/GameModeBase.h"
#include "MM_GameMode.generated.h"
//
/**
 * 
 */

UCLASS()
class MAGICALMAYHEM_API AMM_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMM_GameMode();
	
    void OnActorDied(AActor* Actor);

	UFUNCTION()
	void Respawn(AController* Controller);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMM_Character> CharacterToRespawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<APlayerStart> UserPlayerStart = nullptr;
};
