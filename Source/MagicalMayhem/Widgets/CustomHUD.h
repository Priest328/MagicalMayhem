// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HealthAmmoBarWidget.h"
#include "GameFramework/HUD.h"
#include "CustomHUD.generated.h"

/**
 * 
 */
UCLASS()
class MAGICALMAYHEM_API ACustomHUD : public AHUD
{
	GENERATED_BODY()
public:

	void BeginPlay() override;
	UFUNCTION()
	void UpdateHealth(float Health, float MaxHealth);

public:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UHealthAmmoBarWidget> UserWidget = nullptr;

	UPROPERTY()
	UUserWidget* MyWidget = nullptr;

	UPROPERTY()
	UHealthAmmoBarWidget* HealthAmmoWidget = nullptr;


	
};
