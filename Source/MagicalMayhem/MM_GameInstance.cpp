// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_GameInstance.h"
void UMM_GameInstance::Init()
{
	Super::Init();

	
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMM_GameInstance::OnPreLoadMap);
}

void UMM_GameInstance::OnPreLoadMap(const FString& MapName)
{
	
	OnMapOpen.Broadcast(MapName);
	UE_LOG(LogTemp, Log, TEXT("Map openedddd: %s"), *MapName);
}