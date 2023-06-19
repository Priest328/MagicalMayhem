// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MM_ExtractionZone.generated.h"

UCLASS()
class MAGICALMAYHEM_API AMM_ExtractionZone : public AActor
{
	GENERATED_BODY()

public:
	AMM_ExtractionZone();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* OverlapComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ExtractionSound = nullptr;
};
