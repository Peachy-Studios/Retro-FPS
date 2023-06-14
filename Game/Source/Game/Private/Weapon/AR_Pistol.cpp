// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AR_Pistol.h"
#include "PaperFlipbookComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/PointLightComponent.h"

AAR_Pistol::AAR_Pistol(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void AAR_Pistol::Initialize()
{
	if (!IdleFlipbook)
	{
		UE_LOG(LogTemp, Verbose, TEXT("AAR_WeaponBase: Flipbook is invalid!"));
		return;
	}

	if (!ensure(IsValid(FlipbookComp))) return;

	FlipbookComp->SetFlipbook(IdleFlipbook);

	CaptureComponent->ShowOnlyComponent(FlipbookComp);

}
