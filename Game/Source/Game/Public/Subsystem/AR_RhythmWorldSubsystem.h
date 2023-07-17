// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AR_RhythmWorldSubsystem.generated.h"

/**
 * 
 */

class AAR_BeatsManager;

UCLASS()
class GAME_API UAR_RhythmWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAR_BeatsManager> BeatsManagerClass;

	UPROPERTY()
	AAR_BeatsManager* BeatsManager;

public:
	UAR_RhythmWorldSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FORCEINLINE AAR_BeatsManager* GetBeatsManager() const { return BeatsManager; }
};
