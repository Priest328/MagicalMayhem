// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"

// Sets default values
ABlackHole::ABlackHole()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(MeshComp);

	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComp->SetSphereRadius(100);
	InnerSphereComp->SetupAttachment(MeshComp);

	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComp->SetSphereRadius(600);
	OuterSphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();

	InnerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::ABlackHole::OverlapInnerSphere);
	EnableGravity();
}

void ABlackHole::EnableGravity()
{
	BlackHoleDuration -= 0.035;
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABlackHole::ProcessBlackHoleGravity, 0.035, true);
}

void ABlackHole::ProcessBlackHoleGravity()
{
	BlackHoleDuration -= 0.035;
	if (BlackHoleDuration <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
	else
	{
		TArray<UPrimitiveComponent*> OverlappingComp;
		OuterSphereComp->GetOverlappingComponents(OverlappingComp);

		for (const auto& PrimComp : OverlappingComp)
		{
			if (PrimComp && PrimComp->IsAnySimulatingPhysics())
			{
				const float SphereRadius = OuterSphereComp->GetScaledSphereRadius();
				const float ForceStrength = -3000;

				PrimComp->AddRadialForce(GetActorLocation(),SphereRadius,ForceStrength,ERadialImpulseFalloff::RIF_Constant,true);
			}
		} 
	}
}


void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}
