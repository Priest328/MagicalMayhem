// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/Damageable.h"
#include "HealthComponent.generated.h"

DECLARE_EVENT(UActorHealthComponent, FOnDeath);
DECLARE_EVENT(UActorHealthComponent, FHealthWidget);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICALMAYHEM_API UHealthComponent : public UActorComponent   //, public IDamageable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FHealthWidget HealthWidget;

	FOnDeath OnDeath;

	UPROPERTY(EditAnywhere, Category = "Health")
	float Health = 0.f ;

    UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 0.f;
	
	UFUNCTION()
	void ApplyDamage(float DamageAmount);
};
