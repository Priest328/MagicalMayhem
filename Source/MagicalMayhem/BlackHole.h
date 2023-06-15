// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

UCLASS()
class MAGICALMAYHEM_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void OverlapInnerSphere(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor,
							class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void EnableGravity();

	UFUNCTION()
	void ProcessBlackHoleGravity();

	
public:	

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category = " TimerDuration")
	float BlackHoleDuration = 0.0f;
	
protected:
	UPROPERTY(VisibleAnywhere,Category = "Components")
	UStaticMeshComponent* MeshComp = nullptr;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	USphereComponent* InnerSphereComp = nullptr;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	USphereComponent* OuterSphereComp = nullptr;

private:

	FTimerHandle TimerHandle;
};
