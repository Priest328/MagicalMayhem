#include "MM_AIGurdian.h"
#include "Animation/AnimInstanceProxy.h"
#include "Character/MM_Character.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Navigation/CrowdFollowingComponent.h"

AMM_AIGurdian::AMM_AIGurdian()
{
	PrimaryActorTick.bCanEverTick = false;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnNoiseEmmiterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmmiterComp"));
	
}

void AMM_AIGurdian::BeginPlay()
{
	Super::BeginPlay();
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AMM_AIGurdian::HandleOnSeePawn);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AMM_AIGurdian::HandleOnHearPawn);
	if (bIsPatrolling == true && !PatrolPoints.IsEmpty())
	{
		GetWorldTimerManager().SetTimer(PatrolTimer,this,&AMM_AIGurdian::MoveToNextPatrolPoint,PatrolTimerCheck,true);
	}
}

void AMM_AIGurdian::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMM_AIGurdian::HandleOnSeePawn(APawn* Pawn)
{
	if (AMM_Character* Character = Cast<AMM_Character>(Pawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("OnSeePawn"));
	}
}

void AMM_AIGurdian::HandleOnHearPawn(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (AMM_Character* Character = Cast<AMM_Character>(PawnInstigator))
	{
		UE_LOG(LogTemp, Warning, TEXT("OnHearPawn"));
		DrawDebugSphere(GetWorld(), PawnInstigator->GetActorLocation(), 5, 32, FColor::Emerald, false, 3);

		FVector DirectionVector = Location - GetActorLocation();
		DirectionVector.Normalize();

		FRotator NewRotate = FRotationMatrix::MakeFromX(DirectionVector).Rotator();
		NewRotate.Pitch = 0.0f;
		NewRotate.Roll = 0.0f;

		SetActorRotation(NewRotate);
	}
}

void AMM_AIGurdian::MoveToNextPatrolPoint()
{
	if (bIsPatrolling == true && bIsInLoop == false && bIsInReverseLoop == false)
	{
	}
}
