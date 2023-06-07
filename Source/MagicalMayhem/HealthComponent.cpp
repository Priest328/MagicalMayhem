// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "WallBridge.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}



void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::ApplyDamage(float DamageAmount)
{
	if (DamageAmount <= 0)
	{
		return;
	}
	
	const float HealthBeforeHit = Health;
	Health -= DamageAmount;
	HealthWidget.Broadcast();
	
	UE_LOG(LogTemp, Verbose , TEXT("Health before hit: %.2f Damage amount: %.2f New health: %.2f"), HealthBeforeHit, DamageAmount, Health );
	
	if(Health <= 0)
	{
		OnDeath.Broadcast();
	}
	
}

