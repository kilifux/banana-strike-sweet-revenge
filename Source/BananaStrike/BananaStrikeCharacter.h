// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BananaStrikeCharacter.generated.h"

class AGun;

UCLASS(config=Game)
class ABananaStrikeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SlotOneAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SlotTwoAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RadialMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* BananaMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* BananaMaterialInstance;

	UPROPERTY()
	UMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bWidgetOnScreen = false;

public:
	ABananaStrikeCharacter();

	UFUNCTION(BlueprintCallable)
	void AddCoin();

	UFUNCTION(BlueprintPure)
	int GetCoins() const;

	UFUNCTION()
	void SetCurrentGun(AGun* Gun);

	UFUNCTION()
	AGun* GetCurrentGun() const;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Shoot();

private:
	UPROPERTY(VisibleAnywhere)
	int Coins = 0;

	UPROPERTY(VisibleAnywhere)
	AGun* CurrentGun;
	
	bool bPlayerHasGun = false;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;
	
	float RemapValue;
	
	UPROPERTY(VisibleAnywhere)
	class ABananaPlayerController* BananaPlayerController;

	UPROPERTY(EditDefaultsOnly)
	class UWidgetAnimation* EnterAnimation;

	UPROPERTY()
	TArray<AGun*> EquippedGuns;

public:
	UFUNCTION()
	TArray<AGun*> GetEquippedGuns() const;
	
	UFUNCTION(BlueprintCallable)	//used in WBP_Coins
	void SetEnterCoinWidgetAnimation(UWidgetAnimation* WidgetAnimation);

	UFUNCTION()
	UWidgetAnimation* GetEnterCoinWidgetAnimation() const;

	UFUNCTION()
	void ShowRadialMenuWidget();

	UFUNCTION()
	void RemoveRadialMenuWidget();

	UFUNCTION()
	void AddGunToArray(AGun* Gun);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

