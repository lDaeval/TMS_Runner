// Copyright Epic Games, Inc. All Rights Reserved.

#include "TMS_RunnerCharacter.h"
#include "TMSMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ATMS_RunnerCharacter

ATMS_RunnerCharacter::ATMS_RunnerCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UTMSMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

ESwipeDirection ATMS_RunnerCharacter::FindSwipeDirection(const FVector2D Direction)
{
	int OrthogonalDirection = 0;
	float ValueXY = Direction.X;
	if(FMath::Abs(Direction.X) < FMath::Abs(Direction.Y))
	{
		OrthogonalDirection = 1;
		ValueXY = Direction.Y;
	}

	int SignDirection = 0;
	if(ValueXY < 0)
	{
		SignDirection = 1;
	}

	const ESwipeDirection SwipeDirection = static_cast<ESwipeDirection>((OrthogonalDirection << 1) + SignDirection);

	return SwipeDirection;
}

void ATMS_RunnerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MoveForward(DeltaSeconds * 50);
	
	//
	// if(!ChangeTrailDirection.IsZero())
	// {
	// 	ChangeTrail(DeltaSeconds*50);
	// }
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATMS_RunnerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//PlayerInputComponent->BindAxis("MoveForward", this, &ATMS_RunnerCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &ATMS_RunnerCharacter::MoveRight);

	// handle touch devices
	// PlayerInputComponent->BindTouch(IE_Pressed, this, &ATMS_RunnerCharacter::TouchStarted);
	// PlayerInputComponent->BindTouch(IE_Released, this, &ATMS_RunnerCharacter::TouchStopped);
}


void ATMS_RunnerCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ATMS_RunnerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ATMS_RunnerCharacter::ChangeTrail(float Value)
{
	AddMovementInput(ChangeTrailDirection, Value);
}

void ATMS_RunnerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATMS_RunnerCharacter::MoveRight(float Value)
{
	if(!ChangeTrailDirection.IsZero())
	{
		return;
	}
	
	// if ((Controller != nullptr) && (Value != 0.0f))
	// {
	// 	// find out which way is right
	// 	const FRotator Rotation = Controller->GetControlRotation();
	// 	const FRotator YawRotation(0, Rotation.Yaw*Value, 0);
	//
	// 	// get right vector 
	// 	ChangeTrailDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// }
}
