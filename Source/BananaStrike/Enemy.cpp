// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	MeshComponent = GetMesh();
	DonutMaterial = MeshComponent->GetMaterial(0);
	DonutMaterialInstance = MeshComponent->CreateDynamicMaterialInstance(0, DonutMaterial);
	
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health Enemy left %f"), Health);
	RemapValue = FMath::Clamp(Health / MaxHealth, 0.0f, 1.0f);
	
	if(DonutMaterialInstance)
	{
		DonutMaterialInstance->SetScalarParameterValue("Health_Color", RemapValue);
	}
	
	return DamageToApply;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


