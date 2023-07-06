// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusComponent.h"

#include "Bonus.h"

// Sets default values for this component's properties
UBonusComponent::UBonusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UBonusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(Bonuses.Contains(EBonusType::Score))
	{
		const FString DebugMessage = TEXT("Score bonus: ") + FString::FromInt(Bonuses[EBonusType::Score].Value);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue,
			DebugMessage);
	}
}

void UBonusComponent::BonusCollected(const TScriptInterface<IBonus> Bonus)
{
	if(!IsValid(Bonus.GetObject()))
	{
		return;
	}
	
	EBonusType BonusType = IBonus::Execute_GetBonusType(Bonus.GetObject());
	
	if(!Bonuses.Contains(BonusType))
	{
		FCollectedBonus NewBonus;
		NewBonus.BonusDuration = IBonus::Execute_GetBonusDuration(Bonus.GetObject());
		Bonuses.Add(BonusType) = NewBonus;
	}

	FCollectedBonus& FoundBonus = Bonuses[BonusType];
	FoundBonus.Value++;
	
	auto OnBonusExpired = [this, BonusType]()
	{
		Bonuses.Remove(BonusType);
	};
		
	GetWorld()->GetTimerManager().SetTimer(FoundBonus.ExpirationTime,
		FTimerDelegate::CreateWeakLambda(this, OnBonusExpired),
		FoundBonus.BonusDuration, false);
}

int UBonusComponent::GetBonusValue(EBonusType Type) const
{
	if(!Bonuses.Contains(Type))
	{
		return 1;
	}

	return Bonuses[Type].Value;
}
