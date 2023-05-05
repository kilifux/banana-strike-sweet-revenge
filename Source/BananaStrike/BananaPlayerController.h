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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDCoinsWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDGunCrosshairWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDNoGunCrosshairWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDRadialMenuClass;
	
	UPROPERTY(VisibleAnywhere)
	UUserWidget* HUDGunCrosshairUserWidget;

	UPROPERTY(VisibleAnywhere)
	UUserWidget* HUDNoGunCrosshairUserWidget;

	UPROPERTY(VisibleAnywhere)
	UUserWidget* HUDCoinsUserWidget;

	UPROPERTY(EditAnywhere)
	UUserWidget* HUDRadialMenuWidget;
	
	UPROPERTY(VisibleAnywhere)
	bool bWidgetOnView;

	UPROPERTY()
	bool bRadialButtonHovered;

public:
	UFUNCTION()
	void SetWidgetOnView(bool isWidgetOnView);

	UFUNCTION()
	bool GetWidgetOnView() const;
	
	UFUNCTION()
	void SetGunWidget();

	UFUNCTION()
	void SetNoGunWidget();

	UFUNCTION()
	void SetCoinWidget();

	UFUNCTION()
	void AddRadialMenuWidget();

	UFUNCTION()
	void RemoveRadialMenuWidget();
	
	UFUNCTION()
	UUserWidget* GetCoinsUserWidget() const;

	UFUNCTION(BlueprintCallable)
	void SetRadialButtonHoverd(bool isButtonHovered);

	
};
