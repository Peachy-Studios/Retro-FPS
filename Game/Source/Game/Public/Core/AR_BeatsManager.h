// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AR_BeatsManager.generated.h"

UCLASS()
class GAME_API AAR_BeatsManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAR_BeatsManager();

	FORCEINLINE class UAudioComponent* GetAudioComponent() const { return AudioComponent; }

	//! Getter and setter for current action timestamp
	FORCEINLINE float GetCurrentActionTimeStamp() const { return CurrentActionTimeStamp; }
	FORCEINLINE void SetCurrentActionTimeStamp(const float& Value) { CurrentActionTimeStamp = Value; }

	//! Getter and setter for has action started
	FORCEINLINE bool HasActionStarted() const { return bHasActionStarted; }
	FORCEINLINE void SetHasActionStarted(const bool& Value) { bHasActionStarted = Value; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class UAudioComponent* AudioComponent;
	
	UPROPERTY(EditAnywhere)
	class USoundCue* BeatsCue;

	UPROPERTY()
	class UQuartzSubsystem* QuartzSubsystem;

	UPROPERTY()
	class UQuartzClockHandle* QuartzClockHandle;

	UPROPERTY()
	bool bHasActionStarted = false;

	UPROPERTY()
	float CurrentActionTimeStamp = 0.f;

	UPROPERTY(EditAnywhere)
	float CurrentActionThreshold = 0.2f;


	UFUNCTION()
	void CommandEventBP(EQuartzCommandDelegateSubType EventType, FName Name);

	UFUNCTION()
	void MetronomeEventBP( FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction);
};
