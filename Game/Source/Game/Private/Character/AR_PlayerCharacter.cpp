// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AR_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ChildActorComponent.h"
#include "Weapon/AR_WeaponBase.h"
#include "Weapon/PlayerWeapon.h"
#include "AbilitySystem/AR_AbilitySystemComponent.h"
#include "AbilitySystem/AR_AttributeSet.h"

// Sets default values
AAR_PlayerCharacter::AAR_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Initialize CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	WeaponActor = CreateDefaultSubobject<UChildActorComponent>("WeaponActor");
	WeaponActor->SetupAttachment(FirstPersonCameraComponent);

	ASC = CreateDefaultSubobject<UAR_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	Attributes = CreateDefaultSubobject<UAR_AttributeSet>(TEXT("Attributes"));
}

// Called when the game starts or when spawned
void AAR_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//! Set default input context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	EquipWeapon(AAR_WeaponBase::StaticClass());

	// Setup AbilitySystemComponent
	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);

		if (DefaultAttributeEffects)
		{
			FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
			EffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DefaultAttributeEffects, 1, EffectContext);

			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle GEHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}

		// Set Default attributes
		if (HasAuthority())
		{
			for (TSubclassOf<UGameplayAbility>& StartupAbility : DefaultAbilities)
			{
				ASC->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(), 1, 0));
			}
		}
	}
}


// Called to bind functionality to input
void AAR_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAR_PlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAR_PlayerCharacter::Look);
	}
}

void AAR_PlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!WeaponActor || !WeaponActor->GetChildActor()) return;

	AAR_WeaponBase* Weapon = Cast<AAR_WeaponBase>(WeaponActor->GetChildActor());

	if (!Weapon) return;

	Weapon->WeaponBobbing(GetVelocity().SizeSquared() > 0, DeltaSeconds);
}

void AAR_PlayerCharacter::Move(const FInputActionValue& Value)
{
	// Input is a vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AAR_PlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAR_PlayerCharacter::EquipWeapon(const TSubclassOf<AAR_WeaponBase> Weapon)
{
	if (!ensure(IsValid(WeaponActor)) || !ensure(IsValid(Weapon))) return;

	WeaponActor->SetChildActorClass(Weapon);

	if (!ensure(IsValid(WeaponActor->GetChildActor()))) return;

	if (WeaponActor->GetChildActor()->GetClass()->ImplementsInterface(UPlayerWeapon::StaticClass()))
	{
		Cast<IPlayerWeapon>(WeaponActor->GetChildActor())->Initialize();
	}
}

UAbilitySystemComponent* AAR_PlayerCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

UAR_AbilitySystemComponent* AAR_PlayerCharacter::GetAR_AbilitySystemComponent() const
{
	return ASC;
}
