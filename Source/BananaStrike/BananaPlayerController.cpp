// Fill out your copyright notice in the Description page of Project Settings.


#include "BananaPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void ABananaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUDCoinsUserWidget = CreateWidget(this, HUDCoinsWidgetClass);
	HUDGunCrosshairUserWidget = CreateWidget(this, HUDGunCrosshairWidgetClass);
	HUDNoGunCrosshairUserWidget = CreateWidget(this, HUDNoGunCrosshairWidgetClass);
	HUDRadialMenuWidget = CreateWidget(this, HUDRadialMenuClass);
	
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

void ABananaPlayerController::AddRadialMenuWidget()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.5f);
	HUDRadialMenuWidget->AddToViewport();
	SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this, HUDRadialMenuWidget);
	
}

void ABananaPlayerController::RemoveRadialMenuWidget()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	HUDRadialMenuWidget->RemoveFromParent();
	SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);

	if (bRadialButtonHovered)
	{
		UE_LOG(LogTemp, Warning, TEXT("WLASNIE WYSZEDLES Z BOTTOM BUTTON!"));
	}
}

UUserWidget* ABananaPlayerController::GetCoinsUserWidget() const
{
	return HUDCoinsUserWidget;
}

void ABananaPlayerController::SetRadialButtonHoverd(bool isButtonHovered)
{
	bRadialButtonHovered = isButtonHovered;
}

