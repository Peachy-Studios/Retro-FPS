// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AR_WeaponBase.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperFlipbookComponent.h"
#include "Components/PointLightComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"

// Sets default values
AAR_WeaponBase::AAR_WeaponBase(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	CaptureComponent = ObjectInitializer.GetObj()->CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent"));
	CaptureComponent->SetupAttachment(RootComponent);
	CaptureComponent->ProjectionType = ECameraProjectionMode::Orthographic;
	CaptureComponent->OrthoWidth = 426;
	
	if (RenderTexure) CaptureComponent->TextureTarget = RenderTexure;

	FlipbookComp = ObjectInitializer.GetObj()->CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("WeaponSprite"));
	FlipbookComp->SetupAttachment(CaptureComponent);
	AddInstanceComponent(FlipbookComp);

	FlipbookComp->SetRelativeLocation(FVector(0.f, 100.f, -50.f));
	FlipbookComp->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	FlipbookComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

	UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(), CaptureComponent->TextureTarget, FLinearColor::Black);

	CaptureComponent->ShowOnlyComponent(FlipbookComp);

	FlipbookComp->SetFlipbook(IdleFlipbook);
}

// Called when the game starts or when spawned
void AAR_WeaponBase::BeginPlay()
{
	Super::BeginPlay();

	if (FlipbookComp)
	{
		WeaponInitialLocation = FlipbookComp->GetRelativeLocation();
	}
	
	WeaponPickup();
}


