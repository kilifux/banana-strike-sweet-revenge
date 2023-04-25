// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

#include "BananaPlayerController.h"
#include "BananaStrikeCharacter.h"


// Sets default values
ACoin::ACoin()
{
	
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
	
}

//Moved to Blueprint
/*void ACoin::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	Super::OnCapsuleBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor->IsA<ABananaStrikeCharacter>())
	{
		BananaStrikeCharacter = Cast<ABananaStrikeCharacter>(OtherActor);
		if (BananaStrikeCharacter)
		{
			BananaStrikeCharacter->AddCoin();
			BananaPlayerController = Cast<ABananaPlayerController>(BananaStrikeCharacter->GetController());
			if (BananaPlayerController)
			{
				BananaPlayerController->SetCoinWidget();
			}
			Destroy();
		}
	}
}*/





