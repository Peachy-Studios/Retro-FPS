// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AR_PlayerController.h"

AAR_PlayerController::AAR_PlayerController()
{

}

void AAR_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(HUDClass)) return;

	HUD = CreateWidget<UUserWidget>(this, HUDClass);

	if (!HUD) return;

	HUD->AddToViewport();
}
