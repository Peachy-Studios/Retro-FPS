// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARGA_Pistol.h"
#include "Character/AR_PlayerCharacter.h"
#include "Weapon/AR_WeaponBase.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Core/AR_ObjectPoolManager.h"
#include "Kismet/KismetMathLibrary.h"

UARGA_Pistol::UARGA_Pistol(): Super()
{
	
}

AAR_PlayerCharacter* UARGA_Pistol::GetPlayer() const
{
	return Cast<AAR_PlayerCharacter>(GetAvatarActorFromActorInfo());
}

AAR_WeaponBase* UARGA_Pistol::GetWeapon() const
{
	if(!PlayerCharacter) return nullptr;
	
	return PlayerCharacter->GetCurrentWeapon();
}

AActor* UARGA_Pistol::GetLineTrace()
{
	if(!PlayerCharacter || !GetWorld()) return nullptr;

	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if(!PlayerController) return nullptr;

	const APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;

	if(!CameraManager) return nullptr;

	const FVector StartPos = CameraManager->GetCameraLocation();
	const FVector EndPos = StartPos + (CameraManager->GetCameraRotation().Vector() * WeaponRange);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndPos, ECC_Visibility);

	if(PlayerCharacter && PlayerCharacter->GetBulletHolePoolManager() && !IsValid(Hit.GetActor()))
	{
		PlayerCharacter->GetBulletHolePoolManager()->SpawnPoolObject(Hit.ImpactPoint, UKismetMathLibrary::MakeRotFromX(Hit.ImpactNormal));
	}
	
	return Hit.GetActor();
}

void UARGA_Pistol::Fire()
{
	PlayerCharacter = GetPlayer();
	AAR_WeaponBase* CurrentWeapon = GetWeapon();

	if(!CurrentWeapon) return;

	CurrentWeapon->Fire();

	AActor* HitActor = GetLineTrace();
}
