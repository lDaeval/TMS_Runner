// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TMSGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameValueChanged, int, NewValue);

class UBonusComponent;

UCLASS()
class TMS_RUNNER_API ATMSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATMSGameState();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void IncreaseCoinsCount();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCoinsCount() { return Coins; }

	UFUNCTION(BlueprintCallable)
	void IncreaseScore();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetScore() { return Score; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetBonusValue(EBonusType BonusType) const;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	float BonusDistance = 100.f;

	UPROPERTY(Transient, BlueprintAssignable)
	FGameValueChanged CoinsCountChanged;

	UPROPERTY(Transient, BlueprintAssignable)
	FGameValueChanged ScoreChanged;
	
private:
	int Coins = 0;

	int Score = 0;

	float DistanceFromStart = 0.f;

	TWeakObjectPtr<const UBonusComponent> PlayerBonusComponent = nullptr;
};
