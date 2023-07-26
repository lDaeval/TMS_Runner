// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectablesSpawner.h"
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

	virtual bool operator==(const FObstacleCombination& Other)
	{
		return	Weight == Other.Weight	&&
				Left == Other.Left		&&
				Middle == Other.Middle	&&
				Right == Other.Right;
	}
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
	
	virtual bool operator==(const FCollectablesCombination& Other)
	{
		return	Weight == Other.Weight	&&
				Left == Other.Left		&&
				Middle == Other.Middle	&&
				Right == Other.Right;
	}
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

	template<class TObject>
	TObject* GetWeightedObject(TArray<TObject*> Objects);

	template<class TObject>
	TObject* GenerateUniqueWeightedObject(const TArray<TObject*> Objects, TArray<TObject*>& SkippingObjects);
	
	UFUNCTION(BlueprintCallable)
	FObstacleCombination GetObstaclesSetup();

	UFUNCTION(BlueprintCallable)
	FCollectablesCombination GetCollectablesSetup();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> ObstaclesDT = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> CollectablesDT = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TrailPeriod = 3;

	UPROPERTY(BlueprintReadOnly)
	bool bShouldSpawnObstacles = true;
	
private:
	TArray<FObstacleCombination*> Obstacles;
	TArray<FObstacleCombination*> SkippingObstacles;

	TArray<FCollectablesCombination*> Collectables;
	TArray<FCollectablesCombination*> SkippingCollectables;
};

template<class TObject>
TObject* UTrailManager::GetWeightedObject(TArray<TObject*> Objects)
{
	static_assert(std::is_base_of_v<FWeightedData, TObject>);

	if(Objects.Num() <= 0)
	{
		return nullptr;
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
	
	return Objects[Index];
}

template<class TObject>
TObject* UTrailManager::GenerateUniqueWeightedObject(const TArray<TObject*> Objects, TArray<TObject*>& SkippingObjects)
{
	TObject* GeneratedObject = GetWeightedObject<TObject>(Objects);

	bool bIsUnique = false;
	while (!bIsUnique)
	{
		if(SkippingObjects.Find(GeneratedObject) == INDEX_NONE)
		{
			bIsUnique = true;
		}
		else
		{
			GeneratedObject = GetWeightedObject<TObject>(Objects);
		}
	}

	if(SkippingObjects.Num() == (TrailPeriod < Objects.Num() ? TrailPeriod : Objects.Num() - 1))
	{
		SkippingObjects.RemoveAtSwap(0);
	}
	
	SkippingObjects.Add(GeneratedObject);
	
	return GeneratedObject;
}
