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

void ABananaPlayerController::SetImages(const TArray<UImage*>& ImagesArray)
{
	Images = ImagesArray;
}

TArray<UImage*> ABananaPlayerController::GetImagesArray() const
{
	return Images;
}

int ABananaPlayerController::GetHoveredRadialIndex() const
{
	return HoveredRadialIndex;
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
	
	if (HoveredRadialIndex == 0)
	{
		SetCurrentWeaponFromRadialMenu(HoveredRadialIndex);
	}
	else if (HoveredRadialIndex == 1 && BananaStrikeCharacter->GetEquippedGuns().Num() > 0)
	{
		SetCurrentWeaponFromRadialMenu(HoveredRadialIndex);
	}
	else if (HoveredRadialIndex == 2 && BananaStrikeCharacter->GetEquippedGuns().Num() > 1)
	{
		SetCurrentWeaponFromRadialMenu(HoveredRadialIndex);
	}
	else if (HoveredRadialIndex == 3 && BananaStrikeCharacter->GetEquippedGuns().Num() > 2)
	{
		SetCurrentWeaponFromRadialMenu(HoveredRadialIndex);
	}
}

UUserWidget* ABananaPlayerController::GetCoinsUserWidget() const
{
	return HUDCoinsUserWidget;
}

void ABananaPlayerController::SetHoveredRadialIndex(int Index)
{
	HoveredRadialIndex = Index;
}

void ABananaPlayerController::SetCurrentWeaponFromRadialMenu(int index)
{
	SetGunWidget();
	
	if (BananaStrikeCharacter->GetCurrentGun())
	{
		BananaStrikeCharacter->GetCurrentGun()->SetActorHiddenInGame(true);
		BananaStrikeCharacter->GetCurrentGun()->SetNoGunMode(false);
	}
	
	if (index == 0)
	{
		BananaStrikeCharacter->SetCurrentGun(nullptr);
		SetNoGunWidget();
	}
	else
	{
		BananaStrikeCharacter->SetCurrentGun(BananaStrikeCharacter->GetEquippedGuns()[index - 1]);
		BananaStrikeCharacter->GetCurrentGun()->SetActorHiddenInGame(false);
		BananaStrikeCharacter->GetCurrentGun()->SetNoGunMode(false);
	}
}


