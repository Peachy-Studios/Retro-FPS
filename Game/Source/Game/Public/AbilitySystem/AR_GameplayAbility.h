// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Game.h"
#include "AR_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UAR_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UAR_GameplayAbility();

	// Input to assign to ability
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EAR_AbilityInputID AbilityInputID = EAR_AbilityInputID::None;
	
	// Passive abilities
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EAR_AbilityInputID AbilityID = EAR_AbilityInputID::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool bActivateAbilityOnGranted = false;

	// Function that activate ability on granted
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
