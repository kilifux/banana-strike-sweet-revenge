// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BananaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BANANASTRIKE_API ABananaPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> HUDCoinsWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> HUDGunCrosshairWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> HUDNoGunCrosshairWidgetClass;

	UPROPERTY()
	UUserWidget* HUDGunCrosshairUserWidget;

	UPROPERTY()
	UUserWidget* HUDNoGunCrosshairUserWidget;

	UPROPERTY()
	UUserWidget* HUDCoinsUserWidget;



	
public:
	UFUNCTION()
	void SetGunWidget();

	UFUNCTION()
	void SetNoGunWidget();

	UFUNCTION()
	void SetCoinWidget();
};
