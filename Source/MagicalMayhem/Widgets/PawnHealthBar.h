// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PawnHealthBar.generated.h"

/**
 * 
 */
class UProgressBar;


UCLASS(BlueprintType)
class MAGICALMAYHEM_API UPawnHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PawnHealthBar = nullptr;
	
};
