// Fill out your copyright notice in the Description page of Project Settings.


#include "BananaPlayerController.h"
#include "BananaStrikeCharacter.h"
#include "Blueprint/UserWidget.h"

void ABananaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UUserWidget* HUDCoinsUserWidget = CreateWidget(this, HUDCoinsWidgetClass);

	if (HUDCoinsUserWidget)
	{
		HUDCoinsUserWidget->AddToViewport();
	}

	HUDNoGunCrosshairUserWidget = CreateWidget(this, HUDNoGunCrosshairWidgetClass);
	
	if (HUDNoGunCrosshairUserWidget)
	{
		HUDNoGunCrosshairUserWidget->AddToViewport();
	}
}

void ABananaPlayerController::SetGunWidget()
{
	HUDGunCrosshairUserWidget = CreateWidget(this, HUDGunCrosshairWidgetClass);
	
	if (HUDGunCrosshairUserWidget)
	{
		HUDGunCrosshairUserWidget->AddToViewport();
		if (HUDGunCrosshairUserWidget)
		{
			HUDNoGunCrosshairUserWidget->RemoveFromParent();
		}
	}
}
