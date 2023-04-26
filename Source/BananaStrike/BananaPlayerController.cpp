// Fill out your copyright notice in the Description page of Project Settings.


#include "BananaPlayerController.h"
#include "Blueprint/UserWidget.h"

void ABananaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUDCoinsUserWidget = CreateWidget(this, HUDCoinsWidgetClass);
	HUDGunCrosshairUserWidget = CreateWidget(this, HUDGunCrosshairWidgetClass);
	HUDNoGunCrosshairUserWidget = CreateWidget(this, HUDNoGunCrosshairWidgetClass);
	
	SetCoinWidget();
	SetNoGunWidget();
}


void ABananaPlayerController::SetWidgetOnView(bool isWidgetOnView)
{
	bWidgetOnView = isWidgetOnView;
}

bool ABananaPlayerController::GetWidgetOnView() const
{
	return bWidgetOnView;
}

void ABananaPlayerController::SetGunWidget()
{
	if (HUDGunCrosshairUserWidget && !HUDGunCrosshairUserWidget->IsInViewport())
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
	if (HUDNoGunCrosshairUserWidget && !HUDNoGunCrosshairUserWidget->IsInViewport())
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

UUserWidget* ABananaPlayerController::GetCoinsUserWidget() const
{
	return HUDCoinsUserWidget;
}

