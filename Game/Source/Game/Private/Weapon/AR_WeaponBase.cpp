// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AR_WeaponBase.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperFlipbookComponent.h"
#include "Components/PointLightComponent.h"

// Sets default values
AAR_WeaponBase::AAR_WeaponBase(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	CaptureComponent = ObjectInitializer.GetObj()->CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent"));
	CaptureComponent->SetupAttachment(RootComponent);
	CaptureComponent->ProjectionType = ECameraProjectionMode::Orthographic;
	CaptureComponent->OrthoWidth = 426;

	FlipbookComp = ObjectInitializer.GetObj()->CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("WeaponSprite"));
	FlipbookComp->SetupAttachment(CaptureComponent);
	CaptureComponent->ShowOnlyComponent(FlipbookComp);
	AddInstanceComponent(FlipbookComp);

	PointLight = ObjectInitializer.GetObj()->CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(CaptureComponent);
}

void AAR_WeaponBase::Initialize()
{
	if (!IdleFlipbook)
	{
		UE_LOG(LogTemp, Verbose, TEXT("AAR_WeaponBase: Flipbook is invalid!"));
		return;
	}

	if(!ensure(IsValid(FlipbookComp))) return;

	FlipbookComp->SetFlipbook(IdleFlipbook);
}

// Called when the game starts or when spawned
void AAR_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
}


