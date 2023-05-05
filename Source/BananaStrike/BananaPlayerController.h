// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BananaPlayerController.generated.h"

class UUserWidget;

UCLASS()
class BANANASTRIKE_API ABananaPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDCoinsWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDGunCrosshairWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDNoGunCrosshairWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDRadialMenuClass;
	
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

	UPROPERTY(VisibleAnywhere)
	int HoveredRadialIndex;

	UPROPERTY()
	class ABananaStrikeCharacter* BananaStrikeCharacter;
	
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
	void SetHoveredRadialIndex(int Index);

	UFUNCTION()
	void SetCurrentWeaponFromRadialMenu(int index);

	
};
