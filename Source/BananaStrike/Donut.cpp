// Fill out your copyright notice in the Description page of Project Settings.


#include "Donut.h"
#include "Engine/DamageEvents.h"
#include "BananaStrikeCharacter.h"

void ADonut::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCapsuleBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor->IsA<ABananaStrikeCharacter>())
	{
		ABananaStrikeCharacter* BananaStrikeCharacter = Cast<ABananaStrikeCharacter>(OtherActor);

		if (BananaStrikeCharacter)
		{
			BananaStrikeCharacter->TakeDamage(Damage, FDamageEvent(), GetOwnerController(), this);
		}
		
	}
}

AController* ADonut::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;
	return OwnerPawn->GetController();
}
