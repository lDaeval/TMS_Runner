// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TMSGameState.generated.h"

class UBonusComponent;

UCLASS()
class TMS_RUNNER_API ATMSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATMSGameState();

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void IncreaseCoinsCount() { Coins++; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCoinsCount() { return Coins; }

	UFUNCTION(BlueprintCallable)
	void IncreaseScore();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetScore() { return Score; }

protected:
	virtual void AddPlayerState(APlayerState* PlayerState) override;

	UFUNCTION()
	void OnPawnChanged(APawn* OldPawn, APawn* NewPawn);
	
protected:
	UPROPERTY(EditDefaultsOnly)
	float BonusDistance = 100.f;
	
private:
	int Coins = 0;

	int Score = 0;

	float DistanceFromStart = 0.f;

	TWeakObjectPtr<const UBonusComponent> PlayerBonusComponent = nullptr;
};
