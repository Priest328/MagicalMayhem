// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnProjectileComp.h"

#include "DrawDebugHelpers.h"
#include "Chaos/SparseMatrix.h"


// Sets default values
USpawnProjectileComp::USpawnProjectileComp()
{
	SpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>("SpawnPoint");
	//SpawnPoint->SetupAttachment(GetAttachmentRoot());
	
}

// Called when the game starts or when spawned
void USpawnProjectileComp::BeginPlay()
{
}

// Called every frame

void USpawnProjectileComp::SpawnUnit()
{
	if (ActorToSpawn)
	{
		const FTransform& SpawnTransform = SpawnPoint->GetComponentTransform();
		//UE_LOG(LogTemp,Warning,TEXT("Loc %s"), *SpawnPoint->GetComponentTransform().ToString());
		DrawDebugSphere(GetWorld(),SpawnTransform.GetLocation(),5,10,FColor::Red,false,15);
		AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ActorToSpawn,SpawnTransform);;
	}
}
