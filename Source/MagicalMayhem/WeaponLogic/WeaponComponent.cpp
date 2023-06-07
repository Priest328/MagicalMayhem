//Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "MagicalMayhem/WallBridge.h"


UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	if (Strategies.Num() == 0)
	{
		return;
	}

	if (Cast<IWeaponAttackStrategy>(Strategies[0]))
	{
		CurrentStrategy = Strategies[0];
		CurrentStrategyIndex = 0;
	}
}

void UWeaponComponent::WeaponToShoot()
{
	if ((CurrentAmmoAmount > 0) && CurrentStrategy)
	{
		CurrentStrategy->Shoot(this);
		CurrentStrategy->GetMessage();
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Orange, CurrentStrategy->GetMessage());
		CurrentAmmoAmount--;
		UpdateWeaponWidget.Broadcast();
	}
}


void UWeaponComponent::WeaponReload()
{
	CurrentAmmoAmount = MaxAmmoAmount;
	UpdateWeaponWidget.Broadcast();
}

void UWeaponComponent::ChangeShootStrategy(EShootingStrategy Strategy)
{
	if (Strategies.Num() == 0)
	{
		return;
	}
	if (CurrentStrategy && CurrentStrategy->GetType() == Strategy)
	{
		return;
	}

	if (EShootingStrategy::ProjectileShootStrategy == Strategy)
	{
		if (Cast<IWeaponAttackStrategy>(Strategies[0]))
		{
			CurrentStrategy = Strategies[0];
			CurrentStrategyIndex = 0;
		}
	}

	if (EShootingStrategy::RayCastShootStrategy == Strategy)
	{
		if (Cast<IWeaponAttackStrategy>(Strategies[1]))
		{
			CurrentStrategy = Strategies[1];
			CurrentStrategyIndex = 1;
		}
	}

	UpdateWeaponWidget.Broadcast();
}

void UWeaponComponent::Scroll(int8 value)
{
	const int16 StrategiesAmount = Strategies.Num();

	if (Strategies.Num() == 0)
	{
		return;
	}
	
	if (value == 1)
	{
		CurrentStrategyIndex++;
		
		if (CurrentStrategyIndex == StrategiesAmount)
		{
			CurrentStrategyIndex = 0;
		}
		
		if (Cast<IWeaponAttackStrategy>(Strategies[CurrentStrategyIndex]))
		{
			CurrentStrategy = Strategies[CurrentStrategyIndex];
		}
		
		UpdateWeaponWidget.Broadcast();
	}

	else if (value == -1)
	{
		CurrentStrategyIndex--;
		
		if (CurrentStrategyIndex == -1)
		{
			CurrentStrategyIndex = StrategiesAmount - 1;
		}
		
		if (Cast<IWeaponAttackStrategy>(Strategies[CurrentStrategyIndex]))
		{
			CurrentStrategy = Strategies[CurrentStrategyIndex];
		}
		
		UpdateWeaponWidget.Broadcast();
	}
}
