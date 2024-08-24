// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseGameInstance.h"
#include "ProjectCCharacter.generated.h"
UENUM(BlueprintType)
enum class EDirectionalInput : uint8
{
	VE_Default UMETA(DisplayName = "NOT_MOVING"),
	VE_MovingRight UMETA(DisplayName = "MOVING_RIGHT"),
	HB_MovingLeft UMETA(DisplayName = "MOVINF_LEFT")
};
UCLASS(config=Game)
class AProjectCCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;


	//attack1
	void StartAttack1();
	//attack2
	void StartAttack2();
	//attack3
	void StartAttack3();
	//attack4
	void StartAttack4();

	// when in keyboardmode only
	UFUNCTION(BlueprintCallable)
	void P2KeyboardAttack1();
	UFUNCTION(BlueprintCallable)
	void P2KeyboardAttack2();


	UFUNCTION(BlueprintCallable)
	void P2KeyboardJump();

	UFUNCTION(BlueprintCallable)
	void P2KeyboardStopJumping();

	UFUNCTION(BlueprintCallable)
	void P2KeyboardMoveRight(float _value);


	//damage the player
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damageAmount);

protected:

	/** Called for side to side input */
	void MoveRight(float Val);
	void Tick(float DeltaTime);
	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
	//player health
		//first attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "movement")
	EDirectionalInput directionalInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	AActor* hurtbox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool WasFirstAttackUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool WasSecondAttackUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool WasThirdAttackUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool WasSpecialAttackUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool hasLandedHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AProjectCCharacter* otherplayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float playerHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "model")
	bool isflipped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "model")
	FTransform transform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "model")
	FVector scale;

public:
	AProjectCCharacter();

	
	/** Returns SideViewCameraComponent subobject **/
	//FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }*/
};
