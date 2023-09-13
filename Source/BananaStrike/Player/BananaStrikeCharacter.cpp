// Copyright Epic Games, Inc. All Rights Reserved.

#include "BananaStrikeCharacter.h"

#include "BananaPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/WidgetAnimation.h"
#include "Gun/Gun.h"
#include "Components/Image.h"


//////////////////////////////////////////////////////////////////////////
// ABananaStrikeCharacter

ABananaStrikeCharacter::ABananaStrikeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ABananaStrikeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	BananaPlayerController = Cast<ABananaPlayerController>(GetController());
	Health = MaxHealth;
	MeshComponent = GetMesh();
	BananaMaterial = MeshComponent->GetMaterial(0);
	BananaMaterialInstance = MeshComponent->CreateDynamicMaterialInstance(0, BananaMaterial);

	CurrentGun = nullptr;

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

float ABananaStrikeCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);
	RemapValue = FMath::Clamp(Health / MaxHealth, 0.0f, 1.0f);
	
	if(BananaMaterialInstance)
	{
		BananaMaterialInstance->SetScalarParameterValue("Health_Color", RemapValue);
	}
	
	return DamageToApply;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABananaStrikeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		//Radial Menu
		EnhancedInputComponent->BindAction(RadialMenu, ETriggerEvent::Started, this, &ABananaStrikeCharacter::ShowRadialMenuWidget);
		EnhancedInputComponent->BindAction(RadialMenu, ETriggerEvent::Completed, this, &ABananaStrikeCharacter::RemoveRadialMenuWidget);

		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ABananaStrikeCharacter::Shoot);
		
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABananaStrikeCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABananaStrikeCharacter::Look);

	}

}

void ABananaStrikeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABananaStrikeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABananaStrikeCharacter::Shoot()
{
	if (CurrentGun)
	{
		CurrentGun->PullTrigger();
	}
}

void ABananaStrikeCharacter::SetCurrentGun(AGun* Gun) 
{
	CurrentGun = Gun;
}

AGun* ABananaStrikeCharacter::GetCurrentGun() const
{
	return CurrentGun;
}

TArray<AGun*> ABananaStrikeCharacter::GetEquippedGuns() const
{
	return EquippedGuns;
}

void ABananaStrikeCharacter::SetEnterCoinWidgetAnimation(UWidgetAnimation* WidgetAnimation)
{
	EnterAnimation = WidgetAnimation;
}

UWidgetAnimation* ABananaStrikeCharacter::GetEnterCoinWidgetAnimation() const
{
	return EnterAnimation;
}

void ABananaStrikeCharacter::ShowRadialMenuWidget()
{
	BananaPlayerController->AddRadialMenuWidget();
}

void ABananaStrikeCharacter::RemoveRadialMenuWidget()
{
	BananaPlayerController->RemoveRadialMenuWidget();
}

void ABananaStrikeCharacter::AddGunToArray(AGun* Gun)
{
	EquippedGuns.Add(Gun);
	if (CurrentGun)
	{
		CurrentGun->SetActorHiddenInGame(true);
	}
	
	SetCurrentGun(Gun);
	BananaPlayerController->SetGunWidget();
	BananaPlayerController->GetImagesArray()[Gun->GetGunID()]->SetOpacity(1.f);	//show equipped gun's image in Radial Menu 
}

