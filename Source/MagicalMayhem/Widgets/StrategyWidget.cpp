// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicalMayhem/Widgets/StrategyWidget.h"

#include "Components/TextBlock.h"

void UStrategyWidget::ChangeStrategy(FString Strategy)
{
	StrategyTextBlock->SetText(FText::FromString(FString(Strategy)));
}
