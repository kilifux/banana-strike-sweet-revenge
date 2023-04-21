// Fill out your copyright notice in the Description page of Project Settings.


#include "BananaPlayerController.h"
#include "BananaStrikeCharacter.h"
#include "Blueprint/UserWidget.h"

void ABananaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UUserWidget* HUDCoinsUserWidget = CreateWidget(this, HUDCoins);

	if (HUDCoinsUserWidget != nullptr)
	{
		HUDCoinsUserWidget->AddToViewport();
	}

	UUserWidget* HUDCrosshairUserWidget = CreateWidget(this, HUDCrosshair);
	
	if (HUDCrosshairUserWidget != nullptr)
	{
		HUDCrosshairUserWidget->AddToViewport();
	}
}
