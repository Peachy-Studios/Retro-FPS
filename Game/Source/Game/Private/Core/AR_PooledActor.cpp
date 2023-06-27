// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AR_PooledActor.h"

// Sets default values
AAR_PooledActor::AAR_PooledActor()
{
	
}

void AAR_PooledActor::Deactivate()
{
	SetIsActive(false);

	// Reset Location and Rotation
	TeleportTo(FVector::Zero(), FRotator::ZeroRotator);
	
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawned.Broadcast(this);
}

void AAR_PooledActor::SetIsActive(const bool Value)
{
	bIsActive = Value;
	SetActorHiddenInGame(!bIsActive);
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &AAR_PooledActor::Deactivate, PoolLifeSpan, false);
}

