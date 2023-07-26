// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TMSDebugSettings.generated.h"

/**
 * 
 */
UCLASS(config=Editor, defaultconfig, meta=(DisplayName="Debug Settings"))
class TMS_RUNNER_API UTMSDebugSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UFUNCTION()
	bool ShouldSpawnObstacles() const { return bShouldSpawnObstacles; }
	
private:
	UPROPERTY(EditAnywhere, config, Category=Obstacles, meta=(DisplayName="Should spawn obstacles"))
	bool bShouldSpawnObstacles = true;
};
