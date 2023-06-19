// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_LaunchPad.h"

#include "Character/MM_Character.h"
#include "Kismet/GameplayStatics.h"

AMM_LaunchPad::AMM_LaunchPad()
{
	PrimaryActorTick.bCanEverTick = false;
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(75, 75, 45));
	SetRootComponent(OverlapComp);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	StaticMesh->SetupAttachment(GetRootComponent());

	LaunchStrength = 1000;
	LaunchPitchAngle = 45;
}

void AMM_LaunchPad::BeginPlay()
{
	Super::BeginPlay();
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AMM_LaunchPad::handleOverlap);
}

void AMM_LaunchPad::handleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch = LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	if (AMM_Character* Character = Cast<AMM_Character>(OtherActor))
	{
		Character->LaunchCharacter(LaunchVelocity, true, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation());
	}

	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation());
	}
}
