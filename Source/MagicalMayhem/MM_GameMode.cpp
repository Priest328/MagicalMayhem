// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_GameMode.h"

#include "MagicalMayhem/Character/MM_Character.h"
#include "MM_PlayerController.h"
#include "WallBridge.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnitConversion.h"

//
AMM_GameMode::AMM_GameMode()
{
}


void AMM_GameMode::OnActorDied(AActor* Actor)
{
	if (AWallBridge* WallBridge = Cast<AWallBridge>(Actor))
	{
		if (AMM_Character* CustomCharacter = Cast<AMM_Character>(
			UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			CustomCharacter->UpdateObjectivesProgress(Actor);
		}
	}
}

void AMM_GameMode::Respawn(AController* Controller)
{
	if(Controller)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(UserPlayerStart->GetDefaultObject());
		if (PlayerStart && CharacterToRespawn)
		{
			ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
			ACharacter* NewCharacter = GetWorld()->SpawnActor<ACharacter>(CharacterToRespawn,PlayerStart->GetActorTransform());
			Controller->Possess(NewCharacter);
		}
	}
}

void AMM_GameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (Cast<AMM_Character>(InstigatorPawn))
	{
         InstigatorPawn->Destroy();
	}
	OnCompleteMission();
}

