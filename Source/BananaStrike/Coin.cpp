// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

#include "BananaPlayerController.h"
#include "BananaStrikeCharacter.h"
#include "Blueprint/UserWidget.h"


// Sets default values
ACoin::ACoin()
{

}


void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACoin::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	Super::OnCapsuleBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor->IsA<ABananaStrikeCharacter>())
	{
		BananaStrikeCharacter = Cast<ABananaStrikeCharacter>(OtherActor);
		if (BananaStrikeCharacter)
		{
			HandleCoinCollected();
		}
	}
}

void ACoin::HideCoinWidget()
{
	if (BananaPlayerController->GetWidgetOnView())
	{
		CoinWidget->PlayAnimation(CoinWidgetAnimation, 0, 1, EUMGSequencePlayMode::Reverse);
		BananaPlayerController->SetWidgetOnView(false);
		Destroy();
	}
}

void ACoin::PlayCoinWidgetAnimation()
{
	CoinWidget->PlayAnimation(CoinWidgetAnimation);
	BananaPlayerController->SetWidgetOnView(true);
	TimerDelegate.BindUFunction(this, FName("HideCoinWidget"));
	GetWorld()->GetTimerManager().SetTimer(HideWidgetTimerHandle, TimerDelegate, ShowCoinWidgetTime, false);
}

void ACoin::HandleCoinCollected()
{
	BananaStrikeCharacter->AddCoin();
	CoinWidgetAnimation = BananaStrikeCharacter->GetWidgetAnimation();
	BananaPlayerController = Cast<ABananaPlayerController>(BananaStrikeCharacter->GetController());
	if (BananaPlayerController)
	{
		CoinWidget = BananaPlayerController->GetCoinsUserWidget();
		if (CoinWidget)
		{
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
			if (!BananaPlayerController->GetWidgetOnView())
			{
				PlayCoinWidgetAnimation();
			}
		}
	}
}




