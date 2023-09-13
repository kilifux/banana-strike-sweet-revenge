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

	UPROPERTY()
	TArray<UImage*> Images;
	
protected:
	virtual void BeginPlay() override;

public:
	//Returns images from RadialMenu 
	UFUNCTION()
	TArray<UImage*> GetImagesArray() const;
	
	//Sets images in WBP_RadialMenu
	UFUNCTION(BlueprintCallable)
	void SetImages(const TArray<UImage*>& ImageArray);

	//Gets is Coin Widget on Viewport, use in Coin class
	UFUNCTION()
	bool GetIsCoinWidgetOnView() const;

	//Sets bWidgetOnView variable
	UFUNCTION()
	void SetIsCoinWidgetOnView(bool isWidgetOnView);

	//Sets WBP_GunCrosshair widget
	UFUNCTION()
	void SetGunWidget();

	//Sets WBP_NoGunCrosshair widget
	UFUNCTION()
	void SetNoGunWidget();

	//Returns WBP_Coins widget
	UFUNCTION()
	UUserWidget* GetCoinsWidget() const;
	
	//Adds WBP_Coins widget to viewport
	UFUNCTION()
	void SetCoinWidget();

	//Adds WBP_RadialMenu Widget to viewport
	UFUNCTION()
	void AddRadialMenuWidget();
	
	//Remove WBP_RadialMenu Widget from viewport
	UFUNCTION()
	void RemoveRadialMenuWidget();

	//Sets index depending on the selection of the piece by player on Radial Menu
	UFUNCTION(BlueprintCallable)
	void SetHoveredRadialIndex(int Index);

	//Sets player's current weapon depending on index of selection of the piece
	UFUNCTION()
	void SetCurrentWeaponFromRadialMenu(int index);

	
};
