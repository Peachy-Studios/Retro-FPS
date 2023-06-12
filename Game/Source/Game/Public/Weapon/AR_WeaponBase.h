// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/PlayerWeapon.h"
#include "AR_WeaponBase.generated.h"

UCLASS()
class GAME_API AAR_WeaponBase : public AActor, public IPlayerWeapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* CaptureComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* FlipbookComp;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class UPointLightComponent* PointLight;

public:	
	// Sets default values for this actor's properties
	AAR_WeaponBase(const FObjectInitializer& ObjectInitializer);
	
	/* IPlayerWeapon Interface */
	virtual void Initialize() override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* ShootFlipbook;
};
