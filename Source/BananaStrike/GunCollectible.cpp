// Fill out your copyright notice in the Description page of Project Settings.


#include "GunCollectible.h"

#include "BananaPlayerController.h"
#include "BananaStrikeCharacter.h"
#include "Gun.h"

void AGunCollectible::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	Super::OnCapsuleBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor->IsA<ABananaStrikeCharacter>())
	{
		BananaStrikeCharacter = Cast<ABananaStrikeCharacter>(OtherActor);
		
		if (BananaStrikeCharacter)
		{
			ABananaPlayerController* Controller = Cast<ABananaPlayerController>(BananaStrikeCharacter->GetController());
			if (Controller)
			{
				Gun = GetWorld()->SpawnActor<AGun>(GunClass);
				Gun->AttachToComponent(BananaStrikeCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_socket"));
				Gun->SetOwner(BananaStrikeCharacter);
				BananaStrikeCharacter->SetEquippedGun(Gun);
				Controller->SetGunWidget();
				Destroy();
			}
		}
	}
}


