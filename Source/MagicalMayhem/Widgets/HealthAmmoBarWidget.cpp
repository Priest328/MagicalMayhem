// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAmmoBarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthAmmoBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}



void UHealthAmmoBarWidget::SetHealth(float Health, float MaxHealth)
{
	HealthTextBlock->SetText(FText::FromString(FString::SanitizeFloat(Health)));
	HealthProgressBar->SetPercent(Health/MaxHealth);
}

void UHealthAmmoBarWidget::SetAmmo(int CurrentAmmo, int MaxAmmo)
{
	CurrentAmmoTextBlock->SetText(FText::FromString(FString::FromInt(CurrentAmmo)));
	MaxAmmoTextBlock->SetText(FText::FromString(FString::FromInt(MaxAmmo)));
}



