// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARGA_Shoot.h"
#include "Utils/LogUtil.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Core/AR_BeatsManager.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "Quartz/QuartzSubsystem.h"
#include "Subsystem/AR_RhythmWorldSubsystem.h"


UARGA_Shoot::UARGA_Shoot() : Super()
{
	
}

void UARGA_Shoot::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if(HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if(!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		}

		WaitForEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, WeaponEventTag);
		WaitForEventTask->EventReceived.AddDynamic(this, &UARGA_Shoot::OnEventReceived);

		// Get Timestamp
		UQuartzSubsystem* QuartzSubsystem = GetWorld()->GetSubsystem<UQuartzSubsystem>();
		UAR_RhythmWorldSubsystem* RhythmWorldSystem = GetWorld()->GetSubsystem<UAR_RhythmWorldSubsystem>();

		if(!QuartzSubsystem || ! RhythmWorldSystem) return;
		
		UQuartzClockHandle* ClockHandle = QuartzSubsystem->GetHandleForClock(GetWorld(), FName("Beats Clock"));
		AAR_BeatsManager* BeatsManager = RhythmWorldSystem->GetBeatsManager();

		if(!ClockHandle || ! BeatsManager) return;

		BeatsManager->SetCurrentActionTimeStamp(ClockHandle->GetCurrentTimestamp(GetWorld()).Seconds);
		
		Fire();
		
		FireRateDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, GetCooldownTimeRemaining());
		FireRateDelayTask->OnFinish.AddDynamic(this, &UARGA_Shoot::OnEndAbility);
		FireRateDelayTask->Activate();
	}

}

void UARGA_Shoot::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(IsValid(WaitForEventTask))
	{
		WaitForEventTask->EndTask();
	}

	if(IsValid(FireRateDelayTask))
	{
		FireRateDelayTask->EndTask();
	}
	
	Reset();
}

void UARGA_Shoot::OnEventReceived(FGameplayEventData Payload)
{
	ApplyGameplayEffectToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, Payload.TargetData, GameplayEffect, 1.f);
}

void UARGA_Shoot::OnEndAbility()
{
	check(CurrentActorInfo);
	UE_LOG(LogTemp, Warning, TEXT("Ended"));
	constexpr bool bReplicateEndAbility = true;
	constexpr bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
