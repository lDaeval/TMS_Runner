// Fill out your copyright notice in the Description page of Project Settings.


#include "TMSGameState.h"

#include "Bonus.h"
#include "BonusComponent.h"
#include "GameFramework/PlayerState.h"


// Sets default values
ATMSGameState::ATMSGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATMSGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FString DebugMessage = TEXT("Score: ") + FString::FromInt(Score);
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green,
		DebugMessage);
	
	const APlayerState* Player = PlayerArray[0];
	const APawn* PlayerPawn = Player->GetPawn();

	const float NewDistanceFromStart = PlayerPawn->GetActorLocation().Y;
	if(NewDistanceFromStart - DistanceFromStart > BonusDistance)
	{
		IncreaseScore();
		DistanceFromStart = NewDistanceFromStart;
	}
}

void ATMSGameState::IncreaseScore()
{
	Score += 1 * PlayerBonusComponent->GetBonusValue(EBonusType::Score);
}

void ATMSGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	PlayerState->GetPlayerController()->OnPossessedPawnChanged.AddDynamic(this, &ATMSGameState::OnPawnChanged);
}

void ATMSGameState::OnPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if(!IsValid(NewPawn))
	{
		return;
	}

	PlayerBonusComponent = Cast<UBonusComponent>(NewPawn->FindComponentByClass(UBonusComponent::StaticClass()));
}
