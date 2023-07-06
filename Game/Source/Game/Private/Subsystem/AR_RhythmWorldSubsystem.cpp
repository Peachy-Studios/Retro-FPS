// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/AR_RhythmWorldSubsystem.h"

#include "Core/AR_BeatsManager.h"

UAR_RhythmWorldSubsystem::UAR_RhythmWorldSubsystem()
{
	static ConstructorHelpers::FClassFinder<AAR_BeatsManager> BeatManagerAsset(TEXT("/Game/_Project/Blueprints/Beats/BP_BeatsManager"));
	if(BeatManagerAsset.Succeeded( ))
	{
		BeatsManagerClass = BeatManagerAsset.Class;
	}
}

void UAR_RhythmWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("Rhythm Subsystem has started!!"));

	if(!IsValid(BeatsManagerClass)) return;

	BeatsManager = GetWorld()->SpawnActor<AAR_BeatsManager>();
}


