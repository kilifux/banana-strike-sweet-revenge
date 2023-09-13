// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Player/BananaStrikeCharacter.h"
#include "Player/BananaPlayerState.h"


// Sets default values
ACoin::ACoin()
{
	CoinValue = 2;
}

void ACoin::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	Super::OnCapsuleBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (const ABananaStrikeCharacter* BananaStrikeCharacter = Cast<ABananaStrikeCharacter>(OtherActor))
	{
		if (ABananaPlayerState* BananaPlayerState = Cast<ABananaPlayerState>(BananaStrikeCharacter->GetPlayerState()))
		{
			BananaPlayerState->AddCoins(CoinValue);
		}
	}
}

void ACoin::HideCoinWidget()
{
	//if (BananaPlayerController->GetIsCoinWidgetOnView())
	//{
	//	CoinWidget->PlayAnimation(CoinWidgetAnimation, 0, 1, EUMGSequencePlayMode::Reverse);
	//	BananaPlayerController->SetIsCoinWidgetOnView(false);
	//}
}

void ACoin::PlayCoinWidgetAnimation()
{
	//CoinWidget->PlayAnimation(CoinWidgetAnimation);
	//BananaPlayerController->SetIsCoinWidgetOnView(true);
	//TimerDelegate.BindUFunction(this, FName("HideCoinWidget"));
	//GetWorld()->GetTimerManager().SetTimer(HideWidgetTimerHandle, TimerDelegate, ShowCoinWidgetTime, false);
}

void ACoin::HandleCoinCollected()
{
	//CoinWidgetAnimation = BananaStrikeCharacter->GetEnterCoinWidgetAnimation();
	//
	//if (BananaPlayerController = Cast<ABananaPlayerController>(BananaStrikeCharacter->GetController()))
	//{
	//	if (CoinWidget = BananaPlayerController->GetCoinsWidget())
	//	{
	//		if (!BananaPlayerController->GetIsCoinWidgetOnView())
	//		{
	//			PlayCoinWidgetAnimation();
	//		}
	//	}
	//}
}




