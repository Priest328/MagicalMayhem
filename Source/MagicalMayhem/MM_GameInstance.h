// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MM_GameInstance.generated.h"

/**
 * 
 */
//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMapOpenDelegate, FString, MapName);
UCLASS()
class MAGICALMAYHEM_API UMM_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	virtual void Init() override;

	UPROPERTY(BlueprintAssignable, Category = "Map")
	FOnMapOpenDelegate OnMapOpen;

private:
	void OnPreLoadMap(const FString& MapName);
};
