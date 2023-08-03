// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RunnerSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FSaveGameData
{
	GENERATED_BODY()

	UPROPERTY(SaveGame, BlueprintReadWrite)
	FString PlayerName = TEXT("");

	UPROPERTY(SaveGame, BlueprintReadWrite)
	int TotalScore = 0;
};

/**
 * 
 */
UCLASS()
class TMS_RUNNER_API URunnerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	URunnerSaveGame();
	
	UFUNCTION(BlueprintCallable)
	void AddNewSaveData(const FSaveGameData& NewSaveData);

	FString GetSaveSlotName() const { return SaveSlotName; }
	
protected:
	UPROPERTY(SaveGame, BlueprintReadOnly)
	TArray<FSaveGameData> SaveGameData;

	UPROPERTY(Transient, BlueprintReadOnly)
	FString SaveSlotName = TEXT("");

	UPROPERTY(Transient, BlueprintReadOnly)
	int SavesCount = 9;
};
