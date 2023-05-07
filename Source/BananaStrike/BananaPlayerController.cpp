// Fill out your copyright notice in the Description page of Project Settings.


#include "BananaPlayerController.h"

#include "BananaStrikeCharacter.h"
#include "Gun.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

void ABananaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUDCoinsUserWidget = CreateWidget(this, HUDCoinsWidgetClass);
	HUDGunCrosshairUserWidget = CreateWidget(this, HUDGunCrosshairWidgetClass);
	HUDNoGunCrosshairUserWidget = CreateWidget(this, HUDNoGunCrosshairWidgetClass);
	HUDRadialMenuWidget = CreateWidget(this, HUDRadialMenuClass);
	
	BananaStrikeCharacter = Cast<ABananaStrikeCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	SetCoinWidget();
	SetNoGunWidget();
	
}

TArray<UImage*> ABananaPlayerController::GetImagesArray() const
{
	return Images;
}

void ABananaPlayerController::SetImages(const TArray<UImage*>& ImagesArray)
{
	Images = ImagesArray;
}

bool ABananaPlayerController::GetIsCoinWidgetOnView() const
{
	return bWidgetOnView;
}

void ABananaPlayerController::SetIsCoinWidgetOnView(bool isWidgetOnView)
{
	bWidgetOnView = isWidgetOnView;
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
	SetCurrentWeaponFromRadialMenu(HoveredRadialIndex);
}

UUserWidget* ABananaPlayerController::GetCoinsWidget() const
{
	return HUDCoinsUserWidget;
}

void ABananaPlayerController::SetHoveredRadialIndex(int Index)
{
	HoveredRadialIndex = Index;
}

void ABananaPlayerController::SetCurrentWeaponFromRadialMenu(int index)
{
	if (index == 5)
	{
		return;
	}
	
	if (BananaStrikeCharacter->GetCurrentGun())
	{
		BananaStrikeCharacter->GetCurrentGun()->SetActorHiddenInGame(true);
		BananaStrikeCharacter->GetCurrentGun()->SetNoGunMode(false);
	}
	
	if (index == 0)
	{
		SetNoGunWidget();
		BananaStrikeCharacter->SetCurrentGun(nullptr);
		return;
	}
	
	for (AGun* Gun : BananaStrikeCharacter->GetEquippedGuns())
	{
		SetGunWidget();
		if (Gun->GetGunID() == index)
		{
			BananaStrikeCharacter->SetCurrentGun(Gun);
			BananaStrikeCharacter->GetCurrentGun()->SetActorHiddenInGame(false);
			BananaStrikeCharacter->GetCurrentGun()->SetNoGunMode(false);
		}
	}
}


