// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AR_PooledActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawned, AAR_PooledActor*, PoolActor);

UCLASS()
class GAME_API AAR_PooledActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAR_PooledActor();

	UPROPERTY()
	FOnPooledObjectDespawned OnPooledObjectDespawned;

	UFUNCTION(BlueprintCallable, Category ="Pooled Object")
	void Deactivate();
	
	void SetIsActive(const bool Value);
	FORCEINLINE void SetPoolLifeSpan(const float Value) { PoolLifeSpan = Value; }
	FORCEINLINE void SetPoolIndex(const int32 Value) { PoolIndex = Value; }

	FORCEINLINE bool IsActive() const { return bIsActive; }
	FORCEINLINE int32 GetPoolIndex() const { return PoolIndex; }
protected:
	bool bIsActive;
	float PoolLifeSpan = 0.f;
	int32 PoolIndex;
	FTimerHandle LifeSpanTimer;
};
