// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class BANANASTRIKE_API AEnemy : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY()
	UCapsuleComponent* EnemyCapsuleComponent;
	
	UPROPERTY()
	UMeshComponent* MeshComponent;

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult){}
	
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;
	
	UPROPERTY()
	float RemapValue;

	UPROPERTY(EditAnywhere)
	float Damage = 20;

};
