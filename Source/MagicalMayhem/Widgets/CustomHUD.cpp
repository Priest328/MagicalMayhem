// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHUD.h"

#include "HealthAmmoBarWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ACustomHUD::BeginPlay()
{
	Super::BeginPlay();
	if (UserWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("1"));
		MyWidget = CreateWidget<UHealthAmmoBarWidget>(GetOwningPlayerController(), UserWidget);
		if (MyWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("2"));
			MyWidget->AddToViewport();
		}
	}
}

void ACustomHUD::UpdateHealth(float Health, float MaxHealth)
{
	UserWidget.GetDefaultObject()->SetHealth(Health,MaxHealth);
}

