// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectCCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AProjectCCharacter::AProjectCCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	/*// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera*/

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	playerHealth = 1.00f;
	WasFirstAttackUsed = false;
	WasSecondAttackUsed = false;
	WasThirdAttackUsed = false;
	WasSpecialAttackUsed = false;
	hurtbox = nullptr;
	otherplayer = nullptr;
	isflipped = false;
	hasLandedHit = false;
	directionalInput = EDirectionalInput::VE_Default;
	scale = FVector(0.0f, 0.0f, 0.0f);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectCCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjectCCharacter::MoveRight);

	//binds the four attacks to action mapping set in the engine
	PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &AProjectCCharacter::StartAttack1);
	PlayerInputComponent->BindAction("Attack2", IE_Released, this, &AProjectCCharacter::StartAttack2);
	PlayerInputComponent->BindAction("Attack3", IE_Pressed, this, &AProjectCCharacter::StartAttack3);
	PlayerInputComponent->BindAction("Attack4", IE_Released, this, &AProjectCCharacter::StartAttack4);



	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProjectCCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProjectCCharacter::TouchStopped);
}

void AProjectCCharacter::MoveRight(float Value)
{

	if (Value>0.20f)
	{
		directionalInput = EDirectionalInput::VE_MovingRight;
	}
	else if (Value < -0.20f)
	{
		directionalInput = EDirectionalInput::HB_MovingLeft;
	}
	else
	{
		directionalInput = EDirectionalInput::VE_Default;
	}

	// add movement in that direction
	AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
}

void AProjectCCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AProjectCCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AProjectCCharacter::StartAttack1()
{
	WasFirstAttackUsed = true;
	UE_LOG(LogTemp, Warning, TEXT("Attack 1 used"));
}
void AProjectCCharacter::StartAttack2()
{
	WasSecondAttackUsed = true;

	UE_LOG(LogTemp, Warning, TEXT("Attack 2 used"));
}
void AProjectCCharacter::StartAttack3()
{
	WasThirdAttackUsed = true;

	UE_LOG(LogTemp, Warning, TEXT("Attack 3 used"));
}
void AProjectCCharacter::StartAttack4()
{
	WasSpecialAttackUsed = true;

	UE_LOG(LogTemp, Warning, TEXT("Attack 4 used"));
	
}

void AProjectCCharacter::TakeDamage(float damageAmount)
{

	UE_LOG(LogTemp, Warning, TEXT("taking damage for %f points"), damageAmount);
	if(otherplayer)
	{
		otherplayer->hasLandedHit = true;
	}
	
	playerHealth -= damageAmount;
	if (playerHealth < 0.00f)
	{
		playerHealth = 0.00f;
	}
}
//runs every frame
void AProjectCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (otherplayer)
	{
		if (auto characterMovement = GetCharacterMovement())
		{
			if (auto enemyMovement = otherplayer->GetCharacterMovement())
			{
				if (enemyMovement->GetActorLocation().Y >= characterMovement->GetActorLocation().Y)
				{
					if (isflipped)
					{
						if (auto capsuleComponent = GetCapsuleComponent()->GetChildComponent(1))
						{
							transform = capsuleComponent->GetRelativeTransform();
							scale = transform.GetScale3D();
							scale.Y = -1;
							transform.SetScale3D(scale);
							capsuleComponent->SetRelativeTransform(transform);
						}
						isflipped = false;
					}
				}

					else
					{
						if (!isflipped)
						{
							if (auto capsuleComponent = GetCapsuleComponent()->GetChildComponent(1))
							{
								transform = capsuleComponent->GetRelativeTransform();
								scale = transform.GetScale3D();
								scale.Y = 1;
								transform.SetScale3D(scale);
								capsuleComponent->SetRelativeTransform(transform);
							}
							isflipped = true;
						}
					}
			}
			
		}
	}
}

void AProjectCCharacter::P2KeyboardAttack1()
{
	StartAttack1();
}
void AProjectCCharacter::P2KeyboardAttack2()
{
	StartAttack2();

}
void AProjectCCharacter::P2KeyboardJump()
{
	Jump();
}
void AProjectCCharacter::P2KeyboardStopJumping()
{
	StopJumping();
}
void AProjectCCharacter::P2KeyboardMoveRight(float _value)
{
	MoveRight(_value);
}
