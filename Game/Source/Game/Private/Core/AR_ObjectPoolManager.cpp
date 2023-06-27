// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AR_ObjectPoolManager.h"
#include "Core/AR_PooledActor.h"

// Sets default values for this component's properties
UAR_ObjectPoolManager::UAR_ObjectPoolManager()
{
}

AAR_PooledActor* UAR_ObjectPoolManager::SpawnPoolObject(const FVector& Location, const FRotator& Rotation)
{
	for(AAR_PooledActor* PooledActor : ObjectPool)
	{
		if(!PooledActor || PooledActor->IsActive()) continue;

		PooledActor->TeleportTo(Location, Rotation);
		PooledActor->SetPoolLifeSpan(PooledObjectLifespan);
		PooledActor->SetIsActive(true);
		SpawnedPoolIndex.Add(PooledActor->GetPoolIndex());

		return PooledActor;
	}

	if(SpawnedPoolIndex.Num() > 0)
	{
		const int32 PooledObjectIndex = SpawnedPoolIndex[0];
		SpawnedPoolIndex.Remove(PooledObjectIndex);
		AAR_PooledActor* PooledActor = ObjectPool[PooledObjectIndex];

		if(!PooledActor) return nullptr;

		PooledActor->SetIsActive(false);

		PooledActor->TeleportTo(Location, Rotation);
		PooledActor->SetPoolLifeSpan(PooledObjectLifespan);
		PooledActor->SetIsActive(true);
		SpawnedPoolIndex.Add(PooledActor->GetPoolIndex());

		return PooledActor;
	}
	
	return nullptr;
}

void UAR_ObjectPoolManager::OnPoolObjectDespawned(AAR_PooledActor* PooledActor)
{
	if(!PooledActor) return;
	
	SpawnedPoolIndex.Remove(PooledActor->GetPoolIndex());
}

// Called when the game starts
void UAR_ObjectPoolManager::BeginPlay()
{
	Super::BeginPlay();

	if(!PooledObjectSubclass) return;
	
	UWorld* const World = GetWorld();

	if(!World) return;

	for (int i = 0; i < PoolSize; ++i)
	{
		AAR_PooledActor* PooledActor = World->SpawnActor<AAR_PooledActor>(PooledObjectSubclass, FVector::Zero(), FRotator::ZeroRotator);

		if(!PooledActor) continue;

		PooledActor->SetIsActive(false);
		PooledActor->SetPoolIndex(i);
		PooledActor->OnPooledObjectDespawned.AddDynamic(this, &UAR_ObjectPoolManager::OnPoolObjectDespawned);
		ObjectPool.Add(PooledActor);
	}
}