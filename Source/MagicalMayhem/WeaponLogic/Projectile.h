// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Projectile.generated.h"

UCLASS()
class MAGICALMAYHEM_API AProjectile : public AActor//, public IDamageable
{
	GENERATED_BODY()
	
public:	

	AProjectile();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:

	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 0.f;

	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* StaticMeshComp = nullptr;

	UPROPERTY()
	USphereComponent* SphereComp = nullptr;

	//virtual void TakeDamage(float DamageAmount) override;
	
	UPROPERTY(EditAnywhere, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

};
