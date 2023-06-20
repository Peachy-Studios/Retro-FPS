// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemInterface.h"
#include "AR_PlayerCharacter.generated.h"

class UCameraComponent;
class UAR_AbilitySystemComponent;
class UAR_AttributeSet;

UCLASS()
class GAME_API AAR_PlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* WeaponActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AR/AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UAR_AbilitySystemComponent* ASC;

	UPROPERTY()
	UAR_AttributeSet* Attributes;

	/** Mapping Context */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowedPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	// Sets default values for this character's properties
	AAR_PlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:	
	// Effect to initialize the attribute sets
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="AR/Ability")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffects;

	// Array of default abilities
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AR/Ability")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;

	void EquipWeapon(const TSubclassOf<class AAR_WeaponBase> Weapon);

	UFUNCTION()
	FORCEINLINE class UChildActorComponent* GetWeaponActor() { return WeaponActor; }

	// Inherited via IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAR_AbilitySystemComponent* GetAR_AbilitySystemComponent() const;
};
