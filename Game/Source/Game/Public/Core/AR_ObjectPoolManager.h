// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AR_ObjectPoolManager.generated.h"

class AAR_PooledActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UAR_ObjectPoolManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAR_ObjectPoolManager();

	UFUNCTION(BlueprintCallable, Category="Object Pool")
	AAR_PooledActor* SpawnPoolObject(const FVector& Location, const FRotator& Rotation);

	UFUNCTION()
	void OnPoolObjectDespawned(AAR_PooledActor* PooledActor);
protected:
#pragma region Object Pool Settings
	UPROPERTY(EditAnywhere, Category="Object Pool")
	TSubclassOf<AAR_PooledActor> PooledObjectSubclass;
	UPROPERTY(EditAnywhere, Category="Object Pool")
	int32 PoolSize = 20;
	UPROPERTY(EditAnywhere, Category="Object Pool")
	float PooledObjectLifespan = 0.0f;
#pragma endregion
	
	UPROPERTY()
	TArray<AAR_PooledActor*> ObjectPool;
	UPROPERTY()
	TArray<int32> SpawnedPoolIndex;

	// Called when the game starts
	virtual void BeginPlay() override;
};
