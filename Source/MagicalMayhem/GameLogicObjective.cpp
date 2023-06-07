// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogicObjective.h"

#include "Kismet/GameplayStatics.h"


UGameLogicObjective::UGameLogicObjective()
{

}


bool UGameLogicObjective::DecreaseAmount()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,TEXT("Timer:  "));
	
	if(AmountOfObjects > 0)
	{
		AmountOfObjects -= 1;
		return false;
	}
	else
	{
		return true;
	}
}
//
// void UGameLogicClass::TimerFunction()
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,TEXT("Timer:  "));
// 	TimerTracker -= 1;
// 	if(TimerTracker == 0)
// 	{
// 		UGameplayStatics::OpenLevel(GetWorld(), "NewMap");
// 		GetWorldTimerManager().ClearTimer(TimerHandle);
// 	}
// }
//
// int32 UGameLogicClass::GetAmountOfObjects()
// {
// 	return AmountOfObjects;
// }
//
// void UGameLogicClass::SetAmountOfObjects(int32 Amount)
// {
// 	AmountOfObjects = Amount;
// }
//
