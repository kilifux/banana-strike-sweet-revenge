// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectibles.h"
#include "Coin.generated.h"

UCLASS()
class BANANASTRIKE_API ACoin : public ACollectibles
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

	UFUNCTION()
	void HideCoinWidget();
	
	UFUNCTION()
	void PlayCoinWidgetAnimation();

	//Call the OnCapsuleBeginOverlap function, which is responsible for adding coins to the player and showing the WBP_Coins widget
	UFUNCTION()
	void HandleCoinCollected();

private:
	UPROPERTY(EditAnywhere, Category = "Coin")
	int32 CoinValue;

	TObjectPtr<class ABananaPlayerController> BananaPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUserWidget> CoinWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	class UWidgetAnimation* CoinWidgetAnimation;
	
	FTimerDelegate TimerDelegate;
	FTimerHandle HideWidgetTimerHandle;
	
	float ShowCoinWidgetTime = 5.f;

protected:
	virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
