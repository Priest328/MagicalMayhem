// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpawn_Strategy.h"
#include "MagicalMayhem/Character/MM_Character.h"
#include "DrawDebugHelpers.h"

UProjectileSpawn_Strategy::UProjectileSpawn_Strategy()
{
//	PrimaryComponentTick.bCanEverTick = false;
}

 

void UProjectileSpawn_Strategy::Shoot(UWeaponComponent* WeaponComponent)
{
	if (ActorToSpawn && WeaponComponent)
	{
		if (WeaponComponent->GetWorld())
		{
			const FTransform& SpawnTransform = WeaponComponent->GetComponentTransform();
			UE_LOG(LogTemp,Warning,TEXT("Loc "));
			DrawDebugSphere(WeaponComponent->GetWorld(),WeaponComponent->GetComponentLocation(),5,10,FColor::Red,false,15);
			AActor* NewProjectile = WeaponComponent->GetWorld()->SpawnActor<AActor>(ActorToSpawn,SpawnTransform);
		}
	}
}

EShootingStrategy UProjectileSpawn_Strategy::GetType()
{
  return EShootingStrategy::ProjectileShootStrategy;
}

FString UProjectileSpawn_Strategy::GetMessage()
{
		return Message;
}
// void UProjectileSpawn_Strategy::UpdateAmmoAmount()
// {
// 	UpdateAmmoAmount_Event.Broadcast();
// }
