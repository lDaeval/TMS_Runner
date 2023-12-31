// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TMS_RunnerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDied);

UENUM(BlueprintType)
enum ESwipeDirection
{
	Left = 0, //0x0000
	Right = 1,//0x0001
	Up = 2,	  //0x0010
	Down = 3, //0x0011
};

UCLASS(config=Game)
class ATMS_RunnerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ATMS_RunnerCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure)
	ESwipeDirection FindSwipeDirection(FVector2D Direction);
	
	virtual void Tick(float DeltaSeconds) override;

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void ChangeTrail(float Value);
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	UPROPERTY(BlueprintReadWrite)
	FVector ChangeTrailDirection = FVector::ZeroVector;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDied OnDied;
};

