// Fill out your copyright notice in the Description page of Project Settings.


#include "TrailManager.h"

#include "Algo/Accumulate.h"


// Sets default values for this component's properties
UTrailManager::UTrailManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTrailManager::BeginPlay()
{
	const FString DTContext;
	ObstaclesDT->GetAllRows(DTContext, Obstacles);

	for (FObstacleCombination* Obstacle : Obstacles)
	{
		Obstacle->Weight = FMath::FRandRange(0.f, 1.f);
	}

	CollectablesDT->GetAllRows(DTContext, Collectables);

	// for (FCollectablesCombination* Collectable : Collectables)
	// {
	// 	Collectable->Weight = FMath::FRandRange(0.f, 1.f);
	// }
	
	Super::BeginPlay();
}

FObstacleCombination UTrailManager::GetObstaclesSetup()
{
	return GetWeightedObject<FObstacleCombination>(Obstacles);
}

FCollectablesCombination UTrailManager::GetCollectablesSetup()
{
	return GetWeightedObject<FCollectablesCombination>(Collectables);
}

