// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"
#include <Net/UnrealNetwork.h>
#include "SSaveGame.h"

int32 ASPlayerState::GetCredits()
{
	return Credits;
}

void ASPlayerState::SetCredits(int32 Value)
{
	Credits = Value;
}

void ASPlayerState::AddCredits(int32 Value)
{
	Credits = FMath::Clamp(Credits + Value, 0, 1000);
}

void ASPlayerState::SavePlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject) {
		SaveObject->Credits = Credits;
	}
}

void ASPlayerState::LoadPlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject) {
		//Credits = SaveObject->Credits;
		AddCredits(SaveObject->Credits);
	}
}

void ASPlayerState::OnRep_Credits(int32 OldCredits)
{
	OnCreditsChanged.Broadcast(this, Credits, Credits - OldCredits);
}

void ASPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ASPlayerState, Credits, SharedParams);
}
