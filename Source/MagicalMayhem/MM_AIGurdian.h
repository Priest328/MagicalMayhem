// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "MM_AIGurdian.generated.h"

UCLASS()
class MAGICALMAYHEM_API AMM_AIGurdian : public ACharacter
{
	GENERATED_BODY()

public:
	AMM_AIGurdian();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveToNextPatrolPoint();
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void HandleOnSeePawn(APawn* Pawn);

	UFUNCTION()
	void HandleOnHearPawn( APawn* PawnInstigator, const FVector& Location, float Volume);
	
public:
	UPROPERTY(EditInstanceOnly, Category = "AI")
	UPawnSensingComponent* PawnSensingComponent = nullptr;
	
	UPROPERTY()
	UPawnNoiseEmitterComponent * PawnNoiseEmmiterComp = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	bool bIsPatrolling = false;

    /* If true, Actor will moving in circle of PatrolPoints (e.g. 1st-Point -> 2nd-Point-> 1st-Point*/
	UPROPERTY(EditInstanceOnly, Category = "Patrol", meta = (EditCondition = "bIsPatrolling && !bIsInReverseLoop", EditConditionToggle))
	bool bIsInLoop = false;

	/*If true, Actor will moving in reverse direction (e.g. 1st-Point -> 2nd-Point -> 3rd-Point -> 2nd-Point -> 1st-Point)*/
	UPROPERTY(EditInstanceOnly, Category = "Patrol", meta = (EditCondition = "bIsPatrolling && !bIsInLoop", EditConditionToggle))
	bool bIsInReverseLoop = false;
	
	UPROPERTY(EditInstanceOnly, Category = "Patrol", meta = (EditCondition = "bIsPatrolling"))
	TArray<AActor*> PatrolPoints;

	/*Amount of time to check that Actor is in the correct position to set moving to the next
	 *position or to stop actor on the current location */
	UPROPERTY(EditInstanceOnly,Category = "Patrol")
	float PatrolTimerCheck;
	
private:
	FTimerHandle PatrolTimer;
};
