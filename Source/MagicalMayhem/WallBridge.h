// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "MagicalMayhem/Widgets/PawnHealthBar.h"
#include "GameFramework/Actor.h"
#include "WallBridge.generated.h"



UCLASS()
class MAGICALMAYHEM_API AWallBridge : public AActor//, public IDamageable
{
	GENERATED_BODY()
	
public:	
	AWallBridge();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	
public:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HealthWidgetComponent = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Properties")
	UHealthComponent* HealthComp = nullptr ;

	UPROPERTY(EditAnywhere, Category = "Properties")
	UStaticMeshComponent * StaticMesh = nullptr;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent = nullptr;
	
    UFUNCTION()
	void OnDie();

	UFUNCTION()
	void UpdateWidgetHealth();

	UPROPERTY()
	UPawnHealthBar* HealthBar = nullptr;
	
	//virtual void TakeDamage(float DamageAmount) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
