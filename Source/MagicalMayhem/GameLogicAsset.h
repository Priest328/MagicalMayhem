// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameLogicAsset.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestoyedDelegate);
DECLARE_EVENT_OneParam(UGameLogicAsset,FOnChangeMisionWidget,FString&)

UCLASS()
class MAGICALMAYHEM_API UGameLogicAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

    int GetRemainingObjects();
	
	int GetProgress();

    void ApplyObjectDeath(AActor* DestroyedActor);

	UGameLogicAsset();
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Amount of Objects to destroy")
	int ObjectsToDestroy = 0;
	
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Destroyed Objects")
	int DestroyedObjects = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Actor to Destroy")
	TSubclassOf<AActor> TargetClass = nullptr;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "All Destroyed")
	bool bIsAllDestroyed = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Mission Description")
	FString MissionDescription;
	
	FOnDestoyedDelegate OnCompleted;
	FOnChangeMisionWidget OnChangeMisionWidget;
};
