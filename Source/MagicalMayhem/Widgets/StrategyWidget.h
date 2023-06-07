// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StrategyWidget.generated.h"
/**
 * 
 */
UCLASS(BlueprintType)
class MAGICALMAYHEM_API UStrategyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ChangeStrategy(FString Strategy);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StrategyTextBlock = nullptr;
};
