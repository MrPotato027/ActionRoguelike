// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUpCoin.h"
#include "SPlayerState.h"

ASPickUpCoin::ASPickUpCoin()
{
	AmountToAdd = 5.0f;
}

void ASPickUpCoin::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!bIsActive) return;

	if (InstigatorPawn) {
		ASPlayerState* PlayerState = Cast<ASPlayerState>(InstigatorPawn->GetPlayerState());
		if (PlayerState) {
			PlayerState->AddCredits(AmountToAdd);
			Deactive();
			GetWorldTimerManager().SetTimer(TimerHandle_PickUpItem, this, &ASPickUpCoin::Active_TimeElapsed, ActiveDelay);
		}
	}
}
