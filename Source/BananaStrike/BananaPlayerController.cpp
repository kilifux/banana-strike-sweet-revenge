// Fill out your copyright notice in the Description page of Project Settings.


#include "BananaPlayerController.h"
#include "BananaStrikeCharacter.h"
#include "Blueprint/UserWidget.h"

void ABananaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUDGunCrosshairUserWidget = CreateWidget(this, HUDGunCrosshairWidgetClass);
	HUDNoGunCrosshairUserWidget = CreateWidget(this, HUDNoGunCrosshairWidgetClass);
	HUDCoinsUserWidget = CreateWidget(this, HUDCoinsWidgetClass);
	
	SetNoGunWidget();
	SetCoinWidget();

}

void ABananaPlayerController::SetGunWidget()
{
	if (HUDGunCrosshairUserWidget)
	{
		HUDGunCrosshairUserWidget->AddToViewport();
		
		if (HUDNoGunCrosshairUserWidget)
		{
			HUDNoGunCrosshairUserWidget->RemoveFromParent();
		}
	}
}

void ABananaPlayerController::SetNoGunWidget()
{
	if (HUDNoGunCrosshairUserWidget)
	{
		HUDNoGunCrosshairUserWidget->AddToViewport();

		if (HUDGunCrosshairUserWidget)
		{
			HUDGunCrosshairUserWidget->RemoveFromParent();
		}
	}
}

void ABananaPlayerController::SetCoinWidget()
{
	if (HUDCoinsUserWidget)
	{
		HUDCoinsUserWidget->AddToViewport();
	}
}
