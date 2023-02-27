// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASPlayerState*, PlayerState, int32, NewCredits, int32, Delta);

class USSaveGame;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(ReplicatedUsing = OnRep_Credits, BlueprintReadOnly, Category = "PlayerState")
	int32 Credits;

public:
	UFUNCTION(BlueprintCallable)
	int32 GetCredits();

	UFUNCTION(BlueprintCallable)
	void SetCredits(int32 Value);

	UFUNCTION(BlueprintCallable)
	void AddCredits(int32 Value = 1);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCreditsChanged OnCreditsChanged;

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(USSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(USSaveGame* SaveObject);

	UFUNCTION()
	virtual void OnRep_Credits(int32 OldCredits);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	
};
