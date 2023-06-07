// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MissionWidget.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS(BlueprintType)
class MAGICALMAYHEM_API UMissionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void SetMission(FString& MissionDes);

	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MissionText = nullptr;


};
