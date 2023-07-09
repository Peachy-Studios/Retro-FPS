// Fill out your copyright notice in the Description page of Project Settings.
#include "Core/AR_BeatsManager.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "Quartz/QuartzSubsystem.h"
#include "Utils/LogUtil.h"

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
		UE_LOG(LogRhythm, Error, TEXT("Quartz subsystem not found"));
		return;
	}
	
	FQuartzClockSettings QuartzClockSettings;
	FQuartzTimeSignature TimeSignature;
	TimeSignature.BeatType = EQuartzTimeSignatureQuantization::QuarterNote;
	TimeSignature.NumBeats = 4;
	
	QuartzClockSettings.TimeSignature = TimeSignature;
	QuartzClockSettings.bIgnoreLevelChange = false;
	
	QuartzClockHandle = QuartzSubsystem->CreateNewClock(GetWorld(), TEXT("Beats Clock"), QuartzClockSettings);
	
	FQuartzQuantizationBoundary QuantizationBoundary(EQuartzCommandQuantization::Bar, 1.f, EQuarztQuantizationReference::BarRelative);
	
	FOnQuartzCommandEventBP OnQuartzCommandEventBP;
	FOnQuartzMetronomeEventBP OnQuartzMetronomeEvent;
	
	OnQuartzCommandEventBP.BindDynamic(this, &AAR_BeatsManager::CommandEventBP);
	OnQuartzMetronomeEvent.BindDynamic(this, &AAR_BeatsManager::MetronomeEventBP);
	
	QuartzClockHandle->SetBeatsPerMinute(GetWorld(), FQuartzQuantizationBoundary(), FOnQuartzCommandEventBP(), QuartzClockHandle, 120);
	
	AudioComponent->PlayQuantized(GetWorld(), QuartzClockHandle, QuantizationBoundary, OnQuartzCommandEventBP);
	
	QuartzClockHandle->SubscribeToAllQuantizationEvents(GetWorld(), OnQuartzMetronomeEvent, QuartzClockHandle);
}


void AAR_BeatsManager::CommandEventBP(EQuartzCommandDelegateSubType EventType, FName Name)
{
	switch (EventType)
	{
		case EQuartzCommandDelegateSubType::CommandOnFailedToQueue:
			UE_LOG(LogRhythm, Warning, TEXT("UAR_RhythmWorldSubsystem: Command Failed"));
			break;

		case EQuartzCommandDelegateSubType::CommandOnStarted:
			UE_LOG(LogRhythm, Warning, TEXT("UAR_RhythmWorldSubsystem: Command Started"));
			break;

		case EQuartzCommandDelegateSubType::CommandOnQueued:
			QuartzClockHandle->ResumeClock(GetWorld(), QuartzClockHandle);
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
			UE_LOG(LogRhythm, Warning, TEXT("UAR_RhythmWorldSubsystem: Beat"));
			break;
		
		default:
			break;
	}
}