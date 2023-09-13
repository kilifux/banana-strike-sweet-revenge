// Fill out your copyright notice in the Description page of Project Settings.


#include "GunCollectible.h"
#include "Player/BananaPlayerController.h"
#include "Player/BananaStrikeCharacter.h"
#include "Gun/Gun.h"

void AGunCollectible::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	Super::OnCapsuleBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor->IsA<ABananaStrikeCharacter>())
	{
		BananaStrikeCharacter = Cast<ABananaStrikeCharacter>(OtherActor);
		
		if (BananaStrikeCharacter)
		{
			Gun = GetWorld()->SpawnActor<AGun>(GunClass);
			Gun->SetOwner(BananaStrikeCharacter);
			Gun->AttachToComponent(BananaStrikeCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_socket"));
			BananaStrikeCharacter->AddGunToArray(Gun);
			Destroy();
		}
	}
}


