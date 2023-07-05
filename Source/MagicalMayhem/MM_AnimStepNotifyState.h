// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MM_AnimStepNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class MAGICALMAYHEM_API UMM_AnimStepNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly,Category = "StepNotify")
	float Volume = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly,Category = "StepNotify")
	float Range = 500.0f;
};
