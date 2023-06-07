// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "MagicalMayhem/HealthComponent.h"
#include "MagicalMayhem/WallBridge.h"
#include "Chaos/GeometryParticlesfwd.h"


AProjectile::AProjectile()
{
 
	PrimaryActorTick.bCanEverTick = true;
	


	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComp->SetupAttachment(RootComponent);
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComp->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);

	SetRootComponent(StaticMeshComp);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	//SphereComp->SetupAttachment(GetRootComponent());
    //
	
}

void AProjectile::BeginPlay()
{

	Super::BeginPlay();
	StaticMeshComp->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
		OtherActor->TakeDamage(Damage,FDamageEvent(),nullptr,this);
}


