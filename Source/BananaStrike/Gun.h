// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class BANANASTRIKE_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

	bool GunTrace(FHitResult &Hit, FVector& ShotDirection);
	AController* GetOwnerController() const;

	UFUNCTION()
	void SetCanShoot(bool IsCanShoot);

	UFUNCTION()
	void SetNoGunMode(bool IsNoGunMode);
	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ANiagaraActor> HitEffect;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ANiagaraActor> ShootLineEffect;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 20;
	
	FCollisionQueryParams Params;

	FTimerDelegate TimerDelegate;
	FTimerHandle ShootTimerHandle;
	
	bool bCanShoot;

	bool bNoGunMode;

	UPROPERTY(EditDefaultsOnly)
	float ShootRate;
	

};
