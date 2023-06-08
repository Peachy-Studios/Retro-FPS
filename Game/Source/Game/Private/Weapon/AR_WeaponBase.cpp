// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AR_WeaponBase.h"
#include "Components/SceneCaptureComponent2D.h"
//#include "PaperFlipbookComponent.h"

// Sets default values
AAR_WeaponBase::AAR_WeaponBase()
{
	CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture Component"));
	CaptureComponent->SetupAttachment(RootComponent);
	CaptureComponent->ProjectionType = ECameraProjectionMode::Orthographic;
	CaptureComponent->OrthoWidth = 426;

	/*FlipbookComp = CreateDefaultSubobject<PAPER2UPaperFlipbookComponent>(TEXT("Flipbook Component"));
	FlipbookComp->SetupAttachment(RootComponent);*/

}

// Called when the game starts or when spawned
void AAR_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}


