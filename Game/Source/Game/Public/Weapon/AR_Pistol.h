// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/AR_WeaponBase.h"
#include "AR_Pistol.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AAR_Pistol : public AAR_WeaponBase
{
	GENERATED_BODY()

public:
	AAR_Pistol(const FObjectInitializer& ObjectInitializer);

	virtual void Initialize() override;
	virtual void Fire() override;

	void WeaponFlash() const;
};
