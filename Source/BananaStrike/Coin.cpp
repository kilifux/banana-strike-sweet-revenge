// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

#include "BananaStrikeCharacter.h"
#include "Components/CapsuleComponent.h"
#include "BananaStrikeCharacter.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent->SetGenerateOverlapEvents(true);
	CapsuleComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnCapsuleBeginOverlap);
	SetRootComponent(CapsuleComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(CapsuleComponent);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(0, FMath::RandRange(0, 360),0 ));
	CurrentRotation = GetActorRotation();
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentRotation += FRotator(0, 40, 0 ) * DeltaTime;
	SetActorRotation(CurrentRotation);
}

void ACoin::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ABananaStrikeCharacter>())
	{
		BananaStrikeCharacter = Cast<ABananaStrikeCharacter>(OtherActor);
		BananaStrikeCharacter->AddCoin();
		Destroy();
	}
	
}

