// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AR_WeaponBase.generated.h"

UCLASS()
class GAME_API AAR_WeaponBase : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* CaptureComponent;

	/*UPROPERTY(VisibleAnywhere, Category = Weapon)
	class PAPER2UPaperFlipbookComponent* FlipbookComp;*/
public:	
	// Sets default values for this actor's properties
	AAR_WeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
