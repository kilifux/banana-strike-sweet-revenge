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

	UPROPERTY(VisibleAnywhere)
	UUserWidget* HUDGunCrosshairUserWidget;

	UPROPERTY(VisibleAnywhere)
	UUserWidget* HUDNoGunCrosshairUserWidget;

	UPROPERTY(VisibleAnywhere)
	UUserWidget* HUDCoinsUserWidget;

	UPROPERTY(VisibleAnywhere)
	bool bWidgetOnView;

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
	UUserWidget* GetCoinsUserWidget() const;
};
