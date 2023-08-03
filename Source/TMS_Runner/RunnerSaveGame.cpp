// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerSaveGame.h"

#include "TMS_GameSettings.h"

URunnerSaveGame::URunnerSaveGame()
{
	SaveGameData.Reserve(SavesCount);
	SaveSlotName = GetDefault<UTMS_GameSettings>()->GetSaveSlotName();
}

void URunnerSaveGame::AddNewSaveData(const FSaveGameData& NewSaveData)
{
	auto FindLast = [&NewSaveData](const FSaveGameData& SaveData)
	{
		return SaveData.TotalScore < NewSaveData.TotalScore;
	};

	const int Place = SaveGameData.FindLastByPredicate(FindLast);
	SaveGameData.Insert(NewSaveData, Place);

	if(SaveGameData.Num() > SavesCount)
	{
		SaveGameData.RemoveAt(SavesCount-1, SaveGameData.Num() - SavesCount);
	}
}
