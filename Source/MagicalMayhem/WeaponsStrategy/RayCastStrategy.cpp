// Fill out your copyright notice in the Description page of Project Settings.


#include "RayCastStrategy.h"

#include "DrawDebugHelpers.h"
#include "MagicalMayhem/Character/MM_Character.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
URayCastStrategy::URayCastStrategy()
{

}


// Called when the game starts
// void URayCast_Strategy::BeginPlay()
// {
// 	Super::BeginPlay();
//
// 	// ...
// 	
// }

void URayCastStrategy::Shoot(UWeaponComponent* WeaponComponent)
{
	UE_LOG(LogTemp,Warning,TEXT("RayCast"));
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WeaponComponent->GetWorld(), 0);
	
	if(PlayerController == nullptr)
	{
		return;
	}
	
	FVector Direction = PlayerController->PlayerCameraManager->GetCameraRotation().Vector();
	FVector StartLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + Direction * MaxRayCastLength;
	
	AActor* OwnerActor = WeaponComponent->GetOwner();
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	if(OwnerActor && WeaponComponent->GetWorld())
	{
		//UE_LOG(LogTemp,Warning,TEXT("RayCast2"));
		CollisionQueryParams.AddIgnoredActor(OwnerActor); 
		
		bool bHit = WeaponComponent->GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionQueryParams);
		DrawDebugLine(WeaponComponent->GetWorld(),StartLocation,EndLocation,FColor::Orange,false,3,0,2);
		
		if (bHit)
		{
			AActor* Actor = HitResult.GetActor();
			UHealthComponent* HealthComponent = Actor->FindComponentByClass<UHealthComponent>();
			//UE_LOG(LogTemp,Warning,TEXT("RayCastShoot 1"));
			if (HealthComponent)
			{
			//	UE_LOG(LogTemp,Warning,TEXT("RayCastShoot 2"));
				HealthComponent->ApplyDamage(DamageAmount);
			}
		}
	}
}

EShootingStrategy URayCastStrategy::GetType()
{
	return EShootingStrategy::RayCastShootStrategy;
}

FString URayCastStrategy::GetMessage()
{
		return Message;
}
