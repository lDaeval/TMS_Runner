// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TMSMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TMS_RUNNER_API UTMSMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void PerformSlide();

	UFUNCTION(BlueprintCallable)
	void EndSlide();
	
	bool IsSlide() const { return bIsSlide; }
	
protected:
	bool bIsSlide = false;
	
	UPROPERTY(EditDefaultsOnly)
	float SlideStrength = 500.f;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* StrengthOverTime = nullptr;
	
	uint16 RootMotionSourceID = 0;

	float CapsuleRadius = 0.f;
	float HalfHeight = 0.f;
};
