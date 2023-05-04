// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Donut.generated.h"

/**
 * 
 */
UCLASS()
class BANANASTRIKE_API ADonut : public AEnemy
{
	GENERATED_BODY()

protected:
	virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	AController* GetOwnerController() const;
	
};
