// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AR_WeaponPickup.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "Character/AR_PlayerCharacter.h"
#include "Weapon/AR_WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/PlayerCameraManager.h"

// Sets default values
AAR_WeaponPickup::AAR_WeaponPickup()
{
	Root = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(Root);
	Root->OnComponentBeginOverlap.AddDynamic(this, &AAR_WeaponPickup::PickupWeapon);

	WeaponSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Weapon Sprite"));
	WeaponSprite->SetupAttachment(Root);
	
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAR_WeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAR_WeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld())
	{
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		
		if (!CameraManager || !WeaponSprite) return;
		
		FTransform WeaponTransform =  WeaponSprite->GetComponentTransform();

		FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(WeaponTransform.GetLocation(), CameraManager->GetCameraLocation());

		WeaponSprite->SetWorldRotation(FRotator(0.f, LookAt.Yaw + 90.f, 0.f));
	}
}

void AAR_WeaponPickup::PickupWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AAR_PlayerCharacter* PlayerCharacter = Cast<AAR_PlayerCharacter>(OtherActor);

		if (!PlayerCharacter || !WeaponType) return;

		PlayerCharacter->EquipWeapon(WeaponType);

		Destroy();
	}
}

