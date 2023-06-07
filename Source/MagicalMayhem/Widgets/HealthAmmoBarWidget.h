// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthAmmoBarWidget.generated.h"

/**
 * 
 */
class UProgressBar;
class UTextBlock;

UCLASS(BlueprintType)
class MAGICALMAYHEM_API UHealthAmmoBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void SetHealth(float Health,float MaxHealth);

	UFUNCTION()
	void SetAmmo(int CurrentAmmo, int MaxAmmo);
	
	virtual void NativeConstruct() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthTextBlock = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxAmmoTextBlock = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentAmmoTextBlock = nullptr;



};