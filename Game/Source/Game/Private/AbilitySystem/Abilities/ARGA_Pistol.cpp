// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARGA_Pistol.h"
#include "Character/AR_PlayerCharacter.h"
#include "Weapon/AR_WeaponBase.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"

UARGA_Pistol::UARGA_Pistol(): Super()
{
	
}

AAR_PlayerCharacter* UARGA_Pistol::GetPlayer() const
{
	return Cast<AAR_PlayerCharacter>(GetAvatarActorFromActorInfo());
}

AAR_WeaponBase* UARGA_Pistol::GetWeapon(const AAR_PlayerCharacter* PlayerCharacter) const
{
	if(!PlayerCharacter) return nullptr;
	
	return PlayerCharacter->GetCurrentWeapon();
}

AActor* UARGA_Pistol::GetLineTrace(AAR_PlayerCharacter* PlayerCharacter)
{
	if(!PlayerCharacter || !GetWorld()) return nullptr;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if(!PlayerController) return nullptr;

	APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;

	if(!CameraManager) return nullptr;

	FVector StartPos = CameraManager->GetCameraLocation();
	FVector EndPos = StartPos + (CameraManager->GetCameraRotation().Vector() * WeaponRange);

	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red, true, -1, 0, 1.f);
	
	// FHitResult Hit;
	// GetWorld()->LineTraceSingleByChannel(Hit, );

	return nullptr;
}

void UARGA_Pistol::Fire()
{
	AAR_PlayerCharacter* PlayerCharacter = GetPlayer();
	AAR_WeaponBase* CurrentWeapon = GetWeapon(PlayerCharacter);

	if(!CurrentWeapon) return;

	CurrentWeapon->Fire();

	AActor* HitActor = GetLineTrace(PlayerCharacter);
}
