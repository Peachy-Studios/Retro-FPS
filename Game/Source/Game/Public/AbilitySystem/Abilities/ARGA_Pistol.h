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
	class AAR_WeaponBase* GetWeapon(const AAR_PlayerCharacter* PlayerCharacter) const;
	AActor* GetLineTrace(AAR_PlayerCharacter* PlayerCharacter);
	virtual void Fire() override;
};
