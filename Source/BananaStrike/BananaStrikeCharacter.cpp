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
#include "Gun.h"


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
		
		EnhancedInputComponent->BindAction(SlotOneAction, ETriggerEvent::Triggered, this, &ABananaStrikeCharacter::SetSlotOne);
		EnhancedInputComponent->BindAction(SlotOneAction, ETriggerEvent::Completed, this, &ABananaStrikeCharacter::SetSlotOnePressed);
		EnhancedInputComponent->BindAction(SlotTwoAction, ETriggerEvent::Triggered, this, &ABananaStrikeCharacter::SetSlotTwo);
		EnhancedInputComponent->BindAction(SlotTwoAction, ETriggerEvent::Completed, this, &ABananaStrikeCharacter::SetSlotTwoPressed);

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
	if (EquippedGun)
	{
		EquippedGun->PullTrigger();
	}
}

void ABananaStrikeCharacter::SetSlotOne()
{
	if(!bSlotOnePressed)
	{
		if (BananaPlayerController)
		{
			BananaPlayerController->SetNoGunWidget();
			if (EquippedGun)
			{
				EquippedGun->SetActorHiddenInGame(true);
				EquippedGun->SetNoGunMode(true);
			}
		}
		bSlotOnePressed = true;
	}
}

void ABananaStrikeCharacter::SetSlotTwo()
{
	if(!bSlotTwoPressed)
	{
		if (BananaPlayerController && EquippedGun)
		{
			BananaPlayerController->SetGunWidget();
			EquippedGun->SetActorHiddenInGame(false);
			EquippedGun->SetNoGunMode(false);
		}
		bSlotTwoPressed = true;
	}
}

void ABananaStrikeCharacter::AddCoin()
{
	Coins += 1;
}

int ABananaStrikeCharacter::GetCoins() const
{
	return Coins;
}

void ABananaStrikeCharacter::SetEquippedGun(AGun* Gun) 
{
	EquippedGun = Gun;
}

void ABananaStrikeCharacter::SetSlotOnePressed()
{
	bSlotOnePressed = false;
}

void ABananaStrikeCharacter::SetSlotTwoPressed()
{
	bSlotTwoPressed = false;
}

void ABananaStrikeCharacter::SetEnterCoinWidgetAnimation(UWidgetAnimation* WidgetAnimation)
{
	EnterAnimation = WidgetAnimation;
}

UWidgetAnimation* ABananaStrikeCharacter::GetEnterCoinWidgetAnimation() const
{
	return EnterAnimation;
}

