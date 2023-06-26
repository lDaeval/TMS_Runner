// Fill out your copyright notice in the Description page of Project Settings.


#include "TMSMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"


void UTMSMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	const ACharacter* Character = Cast<ACharacter>(GetPawnOwner());
	CapsuleRadius = Character->GetCapsuleComponent()->GetUnscaledCapsuleRadius();
	HalfHeight = Character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
}

void UTMSMovementComponent::PerformSlide()
{
	// const FVector DashDirection = UpdatedComponent->GetForwardVector().GetSafeNormal();
	//
	// constexpr float Duration = 2.f;
	//
	// constexpr bool bIsAdditive = false;
	// const TSharedPtr<FRootMotionSource_ConstantForce> ConstantForce = MakeShared<FRootMotionSource_ConstantForce>();
	// ConstantForce->InstanceName = FName("AbilityTaskApplyRootMotionConstantForce");
	// ConstantForce->AccumulateMode = bIsAdditive
	// 	                                ? ERootMotionAccumulateMode::Additive
	// 	                                : ERootMotionAccumulateMode::Override;
	// ConstantForce->Priority = 5;
	// ConstantForce->Force = DashDirection * SlideStrength;
	// ConstantForce->Duration = Duration;
	// ConstantForce->StrengthOverTime = StrengthOverTime;
	// ConstantForce->FinishVelocityParams.Mode = ERootMotionFinishVelocityMode::ClampVelocity;
	// ConstantForce->FinishVelocityParams.SetVelocity = FVector::ZeroVector;
	// ConstantForce->FinishVelocityParams.ClampVelocity = 1000.f;
	// //if (bEnableGravity)
	// //{
	// //ConstantForce->Settings.SetFlag(ERootMotionSourceSettingsFlags::IgnoreZAccumulate);
	// //}
	// RootMotionSourceID = ApplyRootMotionSource(ConstantForce);

	Crouch();
}

void UTMSMovementComponent::EndSlide()
{
	UnCrouch();
	// RemoveRootMotionSourceByID(RootMotionSourceID);
	//
	// const ACharacter* Character = Cast<ACharacter>(GetPawnOwner());
	// Character->GetCapsuleComponent()->SetCapsuleSize(CapsuleRadius, HalfHeight);
}
