// Fill out your copyright notice in the Description page of Project Settings.

#include "MM_ExtractionZone.h"
#include "MM_GameMode.h"
#include "Character/MM_Character.h"
#include "Kismet/GameplayStatics.h"

AMM_ExtractionZone::AMM_ExtractionZone()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
    OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(150,150,50));
	SetRootComponent(OverlapComp);

	PrimaryActorTick.bCanEverTick = false;
}

void AMM_ExtractionZone::BeginPlay()
{
	Super::BeginPlay();

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this,&AMM_ExtractionZone::HandleBoxOverlap);
}

void AMM_ExtractionZone::HandleBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(AMM_Character* mm_Character = Cast<AMM_Character>(OtherActor))
	{
		if (AMM_GameMode* GameMode = Cast<AMM_GameMode>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->CompleteMission(mm_Character);
			UGameplayStatics::PlaySound2D(this,ExtractionSound);
		}
	}
}

