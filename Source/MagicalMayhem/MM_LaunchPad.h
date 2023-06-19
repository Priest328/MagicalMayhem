#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MM_LaunchPad.generated.h"

UCLASS()
class MAGICALMAYHEM_API AMM_LaunchPad : public AActor
{
	GENERATED_BODY()

public:
	AMM_LaunchPad();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void handleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchStrength = 0.0f;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchPitchAngle = 0.0f;

	UPROPERTY(EditAnywhere, Category = "LaunchPad")
	UParticleSystem* ParticleSystem;
};
