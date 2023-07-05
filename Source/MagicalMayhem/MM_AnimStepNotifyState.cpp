// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_AnimStepNotifyState.h"

#include "Character/MM_Character.h"
#include "Components/PawnNoiseEmitterComponent.h"

void UMM_AnimStepNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp && MeshComp->GetOwner())
	{
		AMM_Character* Character = Cast<AMM_Character>(MeshComp->GetOwner());
		if (Character)
		{
			
			const FVector &Location = Character->GetActorLocation(); // Set the noise source location

			Character->PawnNoiseEmitterComp->MakeNoise(Character,Volume, Location);
		}
	}
}
