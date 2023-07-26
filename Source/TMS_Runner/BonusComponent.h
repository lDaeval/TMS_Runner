// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Bonus.h"
#include "BonusComponent.generated.h"

USTRUCT(BlueprintType)
struct FCollectedBonus
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float BonusDuration = 1.f;

	UPROPERTY(BlueprintReadOnly)
	int Value = 1;

	FTimerHandle ExpirationTime;

	void operator=(const FCollectedBonus& Other)
	{
		BonusDuration = Other.BonusDuration;
		Value = Other.Value;
		ExpirationTime = Other.ExpirationTime;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBonusChanged, EBonusType, BonusType, const FCollectedBonus&, BonusInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBonusExpiration, EBonusType, BonusType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TMS_RUNNER_API UBonusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBonusComponent();

	UFUNCTION(BlueprintCallable)
	void BonusCollected(const TScriptInterface<IBonus> Bonus);

	int GetBonusValue(EBonusType Type) const;

protected:
	UPROPERTY(BlueprintAssignable)
	FBonusChanged OnBonusAdded;

	UPROPERTY(BlueprintAssignable)
	FBonusExpiration OnBonusRemoved;
	
private:
	TMap<EBonusType, FCollectedBonus> Bonuses;
};
