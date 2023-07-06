// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Bonus.h"
#include "BonusComponent.generated.h"


USTRUCT()
struct FCollectedBonus
{
	GENERATED_BODY()

	UPROPERTY()
	float BonusDuration = 1.f;

	int Value = 1;

	FTimerHandle ExpirationTime;

	void operator=(const FCollectedBonus& Other)
	{
		BonusDuration = Other.BonusDuration;
		Value = Other.Value;
		ExpirationTime = Other.ExpirationTime;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TMS_RUNNER_API UBonusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBonusComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void BonusCollected(const TScriptInterface<IBonus> Bonus);

	int GetBonusValue(EBonusType Type) const;

private:
	TMap<EBonusType, FCollectedBonus> Bonuses;
};
