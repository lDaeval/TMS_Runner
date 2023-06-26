// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Obstacle.h"
#include "Algo/Accumulate.h"
#include "Engine/DataTable.h"
#include "TrailManager.generated.h"

class ACollectablesSpawner;

USTRUCT(BlueprintType)
struct FWeightedData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient)
	float Weight = 1.f;
};

USTRUCT(BlueprintType)
struct FObstacleCombination : public FWeightedData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AObstacle> Left;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AObstacle> Middle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AObstacle> Right;
};

USTRUCT(BlueprintType)
struct FCollectablesCombination : public FWeightedData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ACollectablesSpawner> Left;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ACollectablesSpawner> Middle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ACollectablesSpawner> Right;
};

UCLASS(ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class TMS_RUNNER_API UTrailManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTrailManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	template<class Object>
	Object GetWeightedObject(TArray<Object*> Objects);

	UFUNCTION(BlueprintCallable)
	FObstacleCombination GetObstaclesSetup();

	UFUNCTION(BlueprintCallable)
	FCollectablesCombination GetCollectablesSetup();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> ObstaclesDT = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> CollectablesDT = nullptr;
	
	TArray<FObstacleCombination*> Obstacles;

	TArray<FCollectablesCombination*> Collectables;
};

template<class TObject>
TObject UTrailManager::GetWeightedObject(TArray<TObject*> Objects)
{
	static_assert(std::is_base_of_v<FWeightedData, TObject>);

	if(Objects.Num() <= 0)
	{
		return TObject();
	}
	
	const float TotalWeight = Algo::Accumulate(Objects, 0.f, [](float Weight, const FWeightedData* Object)
	{
		return Weight + Object->Weight;
	});

	const float Random = FMath::RandRange(0.f, TotalWeight);

	Algo::Sort(Objects, [](const FWeightedData* Object1, const FWeightedData* Object2)
	{
		return Object1->Weight < Object2->Weight;
	});

	float CurrentWeight = 0.f;
	int Index = 0;
	for(; Index < Objects.Num(); Index++)
	{
		CurrentWeight += Objects[Index]->Weight;
		if(CurrentWeight >= Random)
		{
			break;
		}
	}
	
	return *Objects[Index];
}