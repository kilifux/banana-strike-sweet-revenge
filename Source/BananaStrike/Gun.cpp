// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "BananaStrikeCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraActor.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGun::PullTrigger()
{
	if (!bCanShoot) return;
	
	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);
	
	if (bSuccess)
	{
		bCanShoot = false;
		GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this, &AGun::ResetCanShoot, ShootRate, false);
		GetWorld()->SpawnActor<ANiagaraActor>(ShootEffect, Hit.Location, ShotDirection.Rotation());

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

void AGun::ResetCanShoot()
{
	bCanShoot = true;
}

