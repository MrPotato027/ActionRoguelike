// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(ReplicatedUsing = OnRep_Credits, BlueprintReadOnly, Category = PlayerState)
	int32 Credits;

public:
	UFUNCTION(BlueprintCallable)
	int32 GetCredits();

	UFUNCTION(BlueprintCallable)
	void SetCredits(int32 Value);

	UFUNCTION(BlueprintCallable)
	void AddCredits(int32 Value = 1);

	UFUNCTION()
	virtual void OnRep_Credits();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	
};
