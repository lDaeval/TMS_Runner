// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TMS_GameSettings.generated.h"

/**
 * 
 */
UCLASS(config=Editor, defaultconfig, meta=(DisplayName="Debug Settings"))
class TMS_RUNNER_API UTMS_GameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UFUNCTION()
	FString GetSaveSlotName() const { return SaveSlotName; }
	
private:
	UPROPERTY(EditAnywhere, config, Category=SaveGame, meta=(DisplayName="Save Slot Name"))
	FString SaveSlotName = TEXT("TMS_Runner");
};
