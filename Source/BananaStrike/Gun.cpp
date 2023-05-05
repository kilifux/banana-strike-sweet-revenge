// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "NiagaraActor.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point Component"));
	ProjectileSpawnPoint->SetupAttachment(StaticMeshComponent);
	
	bCanShoot = true;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

}

void AGun::PullTrigger()
{
	if (bNoGunMode) return;
	if (!bCanShoot) return;
	
	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);
	
	if (bSuccess)
	{
		bCanShoot = false;
		TimerDelegate.BindUFunction(this, FName("SetCanShoot"), true);
		GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, TimerDelegate, ShootRate, false);
		GetWorld()->SpawnActor<ANiagaraActor>(HitEffect, Hit.Location, ShotDirection.Rotation());
		FVector ToTarget = Hit.Location - ProjectileSpawnPoint->GetComponentLocation();
		GetWorld()->SpawnActor<ANiagaraActor>(ShootLineEffect, ProjectileSpawnPoint->GetComponentLocation(), ToTarget.Rotation());

		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
		}
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	if (GetOwnerController() == nullptr)
		return false;
	
	FVector Location;
	FRotator Rotation;
	ShotDirection = -Rotation.Vector();
	GetOwnerController()->GetPlayerViewPoint(Location ,Rotation);
	
	FVector End = Location + Rotation.Vector() * MaxRange;
	TArray<AActor*> Actors {this, GetOwner()};
	Params.AddIgnoredActors(Actors);
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;
	return OwnerPawn->GetController();
}

void AGun::SetCanShoot(bool IsCanShoot)
{
	bCanShoot = IsCanShoot;
}

void AGun::SetNoGunMode(bool IsNoGunMode)
{
	bNoGunMode = IsNoGunMode;
}

