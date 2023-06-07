// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionWidget.h"

#include "Components/TextBlock.h"

void UMissionWidget::SetMission(FString& MissionDes)
{
	MissionText->SetText(FText::FromString(MissionDes));
}
