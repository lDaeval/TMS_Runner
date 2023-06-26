// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TMSGameState.generated.h"

UCLASS()
class TMS_RUNNER_API ATMSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATMSGameState();

	UFUNCTION(BlueprintCallable)
	void IncreaseCoinsCount() { Coins++; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCoinsCount() { return Coins; }

	UFUNCTION(BlueprintCallable)
	void IncreaseScore() { Score++; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetScore() { return Score; }
	
private:
	int Coins = 0;

	int Score = 0;
	
};
