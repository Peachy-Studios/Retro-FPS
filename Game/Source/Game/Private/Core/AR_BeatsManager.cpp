// Fill out your copyright notice in the Description page of Project Settings.
#include "Core/AR_BeatsManager.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "Quartz/QuartzSubsystem.h"

// Sets default values
AAR_BeatsManager::AAR_BeatsManager()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Beats Player"));
	SetRootComponent(AudioComponent);
}

// Called when the game starts or when spawned
void AAR_BeatsManager::BeginPlay()
{
	Super::BeginPlay();

	if(!AudioComponent) return;
	
	AudioComponent->Sound = BeatsCue;
	
	// Get Quartz Subsystem
	QuartzSubsystem = GetWorld()->GetSubsystem<UQuartzSubsystem>();

	if(!IsValid(QuartzSubsystem))
	{
		UE_LOG(LogTemp, Error, TEXT("Quartz subsystem not found"));
		return;
	}

	FQuartzClockSettings QuartzClockSettings;
	QuartzClockHandle = QuartzSubsystem->CreateNewClock(GetWorld(), TEXT("Beats Clock"), QuartzClockSettings);

	FQuartzQuantizationBoundary QuantizationBoundary;
	FOnQuartzCommandEventBP OnQuartzCommandEventBP;
	FOnQuartzMetronomeEventBP OnQuartzMetronomeEvent;

	OnQuartzCommandEventBP.BindDynamic(this, &AAR_BeatsManager::CommandEventBP);
	OnQuartzMetronomeEvent.BindDynamic(this, &AAR_BeatsManager::MetronomeEventBP);
	
	QuartzClockHandle->SetBeatsPerMinute(GetWorld(), QuantizationBoundary, OnQuartzCommandEventBP, QuartzClockHandle, 120);
	QuartzClockHandle->SubscribeToQuantizationEvent(GetWorld(), EQuartzCommandQuantization::Beat, OnQuartzMetronomeEvent, QuartzClockHandle);

	AudioComponent->PlayQuantized(this, QuartzClockHandle, QuantizationBoundary, OnQuartzCommandEventBP);
}


void AAR_BeatsManager::CommandEventBP(EQuartzCommandDelegateSubType EventType, FName Name)
{
	switch (EventType)
	{
	case EQuartzCommandDelegateSubType::CommandOnFailedToQueue:
		break;

	case EQuartzCommandDelegateSubType::CommandOnStarted:
		UE_LOG(LogTemp, Warning, TEXT("UAR_RhythmWorldSubsystem: Command Started"));
		break;

	default:
		break;
	}
}

void AAR_BeatsManager::MetronomeEventBP(FName ClockName, EQuartzCommandQuantization QuantizationType,
	int32 NumBars, int32 Beat, float BeatFraction)
{
	switch (QuantizationType)
	{
	case EQuartzCommandQuantization::Beat:
		UE_LOG(LogTemp, Warning, TEXT("UAR_RhythmWorldSubsystem: Beat"));
		break;
	
	default:
		break;
	}
}