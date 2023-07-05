// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_AnimStepNotify.h"

#include "Character/MM_Character.h"


void UMM_AnimStepNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (AMM_Character* Character = Cast<AMM_Character>(MeshComp->GetOwner()))
	{
		FVector Location = Character->GetActorLocation(); // Set the noise source location

		Character->MakeNoise(Volume, Character, Location, Range);
	}
}
