// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BananaPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCoinsChanged, ABananaPlayerState*, PlayerState, int32, NewCredits);

UCLASS()
class BANANASTRIKE_API ABananaPlayerState : public APlayerState
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Coins")
	int32 Coins;

public:
	UFUNCTION(BlueprintPure, Category = "Coins")
	int32 GetCoins() const { return Coins; }

	UFUNCTION(BlueprintCallable, Category = "Coins")
	void AddCoins(int32 Value);

	FOnCoinsChanged OnCoinsChanged;
	
};
