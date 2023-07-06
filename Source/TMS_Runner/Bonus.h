// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Bonus.generated.h"

UENUM(BlueprintType)
enum class EBonusType : uint8
{
	None,
	Score
};

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI)
class UBonus : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TMS_RUNNER_API IBonus
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent)
	float GetBonusDuration() const;

	UFUNCTION(BlueprintImplementableEvent)
	EBonusType GetBonusType() const;
};
