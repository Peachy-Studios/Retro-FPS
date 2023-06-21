// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AR_GameplayAbility.h"
#include "ARGA_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UARGA_Shoot : public UAR_GameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AR/Tags", meta = (AllowPrivateAccess="true"))
	FGameplayTag WeaponEventTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AR/Effects", meta = (AllowPrivateAccess="true"))
	TSubclassOf<UGameplayEffect> GameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AR/Settings", meta = (AllowPrivateAccess="true"))
	float WeaponRange;
	
	UPROPERTY()
	class UAbilityTask_WaitGameplayEvent* WaitForEventTask;

	UPROPERTY()
	class UAbilityTask_WaitDelay* FireRateDelayTask;
	
	UFUNCTION()
	void OnEventReceived(FGameplayEventData Payload);

	UFUNCTION()
	void OnEndAbility();
	
public:
	UARGA_Shoot();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	virtual void Fire() {};
	virtual void Reset() {};

};
