// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogicAsset.h"

#include "MagicalMayhem/Character/MM_Character.h"
#include "Kismet/GameplayStatics.h"

UGameLogicAsset::UGameLogicAsset()
{
}


int UGameLogicAsset::GetProgress()
{
	return DestroyedObjects;
}

int UGameLogicAsset::GetRemainingObjects()
{
	return ObjectsToDestroy;
}

void UGameLogicAsset::ApplyObjectDeath(AActor* DestroyedActor)
{
	if (DestroyedActor->GetClass() == TargetClass)
	{
		ObjectsToDestroy -= 1;

		if (ObjectsToDestroy == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Broadcast"));
			bIsAllDestroyed = true;
			OnCompleted.Broadcast();
			FString MissionComplete = "Mission Complete";
			OnChangeMisionWidget.Broadcast(MissionComplete);
		}
	}
}
