// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ARGA_Shoot.h"
#include "ARGA_Pistol.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UARGA_Pistol : public UARGA_Shoot
{
	GENERATED_BODY()

public:
	UARGA_Pistol();

	class AAR_PlayerCharacter* GetPlayer() const;
	class AAR_WeaponBase* GetWeapon() const;
	AActor* GetLineTrace();
	virtual void Fire() override;

protected:
	UPROPERTY()
	class AAR_PlayerCharacter* PlayerCharacter;
};
