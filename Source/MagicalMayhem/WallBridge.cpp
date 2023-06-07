// Fill out your copyright notice in the Description page of Project Settings.


#include "WallBridge.h"

#include "MM_GameMode.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWallBridge::AWallBridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	BoxComponent->SetCollisionProfileName(TEXT("BlockAll"));
	BoxComponent->SetGenerateOverlapEvents(false);
	SetRootComponent(BoxComponent);
    
    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
    HealthWidgetComponent->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	HealthComp->OnDeath.AddUObject(this, &AWallBridge::OnDie);
}

// Called when the game starts or when spawned
void AWallBridge::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay called"));
	Super::BeginPlay();
	HealthComp->HealthWidget.AddUObject(this, &AWallBridge::UpdateWidgetHealth);
	HealthBar = Cast<UPawnHealthBar>(HealthWidgetComponent->GetWidget());
	if(HealthBar)
	{
		HealthBar->PawnHealthBar->SetPercent(HealthComp->Health/HealthComp->MaxHealth);
	}
}

// Called every frame
void AWallBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
void AWallBridge::OnDie()
{
	if(AMM_GameMode* GameMode = Cast<AMM_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
      GameMode->OnActorDied(this);
	}
	
	Destroy();
}

float AWallBridge::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HealthComp->ApplyDamage(DamageAmount);
	return DamageAmount;
}

void AWallBridge::UpdateWidgetHealth()
{

	if (HealthBar)
	{
		HealthBar->PawnHealthBar->SetPercent(HealthComp->Health/HealthComp->MaxHealth);
	}
}

// void AWallBridge::TakeDamage(float DamageAmount)
// {
// 	UE_LOG(LogTemp, Warning, TEXT("Tick23131 %f"),HealthComp->Health );
// 	HealthComp->ApplyDamage(DamageAmount);
// }
