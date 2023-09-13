// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectibles.h"
#include "GunCollectible.generated.h"

/**
 * 
 */

class AGun;

UCLASS()
class BANANASTRIKE_API AGunCollectible : public ACollectibles
{
	GENERATED_BODY()

protected:
	virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AGun> Gun;
};
