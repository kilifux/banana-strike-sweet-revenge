// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BananaPlayerState.h"

void ABananaPlayerState::AddCoins(int32 Value)
{
	Coins += Value;
	OnCoinsChanged.Broadcast(this, Coins);
	UE_LOG(LogTemp, Warning, TEXT("Coins: %d"), Coins);
}
