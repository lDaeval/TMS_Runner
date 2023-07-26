// Fill out your copyright notice in the Description page of Project Settings.


#include "TMSGameState.h"

#include "Bonus.h"
#include "BonusComponent.h"
#include "TMS_GameSettings.h"
#include "GameFramework/PlayerState.h"


// Sets default values
ATMSGameState::ATMSGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ATMSGameState::BeginPlay()
{
	Super::BeginPlay();

	PlayerBonusComponent = Cast<UBonusComponent>(FindComponentByClass(UBonusComponent::StaticClass()));

	PrimaryActorTick.SetTickFunctionEnable(true);
}

void ATMSGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const APlayerState* Player = PlayerArray[0];
	const APawn* PlayerPawn = Player->GetPawn();

	if (!PlayerPawn)
	{
		return;
	}

	const float NewDistanceFromStart = PlayerPawn->GetActorLocation().Y;
	if (NewDistanceFromStart - DistanceFromStart > BonusDistance)
	{
		IncreaseScore();
		DistanceFromStart = NewDistanceFromStart;
	}
}

void ATMSGameState::IncreaseCoinsCount()
{
	Coins++;
	CoinsCountChanged.Broadcast(Coins);
}

void ATMSGameState::IncreaseScore()
{
	Score += 1 * PlayerBonusComponent->GetBonusValue(EBonusType::Score);
	ScoreChanged.Broadcast(Score);
}

int ATMSGameState::GetBonusValue(const EBonusType BonusType) const
{
	return PlayerBonusComponent->GetBonusValue(BonusType);
}
