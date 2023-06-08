// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "AR_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AAR_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAR_PlayerController();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	class UUserWidget* HUD;

	virtual void BeginPlay() override;
	
};
