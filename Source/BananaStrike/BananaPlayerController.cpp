// Fill out your copyright notice in the Description page of Project Settings.


#include "BananaPlayerController.h"
#include "BananaStrikeCharacter.h"
#include "Blueprint/UserWidget.h"

void ABananaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UUserWidget* HUD = CreateWidget(this, HUDClass);

	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
}
