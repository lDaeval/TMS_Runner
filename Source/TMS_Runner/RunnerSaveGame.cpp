// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerSaveGame.h"

#include "TMS_GameSettings.h"

URunnerSaveGame::URunnerSaveGame()
{
	SaveGameData.Reserve(9);
	SaveSlotName = GetDefault<UTMS_GameSettings>()->GetSaveSlotName();
}

void URunnerSaveGame::AddNewSaveData(const FSaveGameData& NewSaveData)
{
	SaveGameData.Add(NewSaveData);
}
