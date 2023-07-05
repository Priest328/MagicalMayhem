// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "MM_AnimStepNotify.generated.h"

UCLASS()
class MAGICALMAYHEM_API UMM_AnimStepNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly,Category = "StepNotify")
	float Volume = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly,Category = "StepNotify")
	float Range = 500.0f;
	
};