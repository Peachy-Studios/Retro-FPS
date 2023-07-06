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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	class UAudioComponent* AudioComponent;
	
	UPROPERTY(EditAnywhere)
	class USoundCue* BeatsCue;

	UPROPERTY()
	class UQuartzSubsystem* QuartzSubsystem;

	UPROPERTY()
	class UQuartzClockHandle* QuartzClockHandle;

	UFUNCTION()
	void CommandEventBP(EQuartzCommandDelegateSubType EventType, FName Name);

	UFUNCTION()
	void MetronomeEventBP( FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction);
};
