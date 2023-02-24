// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionEffect.h"
#include "SActionEffect_ThornsBuff.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USActionEffect_ThornsBuff : public USActionEffect
{
	GENERATED_BODY()

public:
	USActionEffect_ThornsBuff();

	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;

	void ExecutePeriodicEffect_Implementation(AActor* Instigator) override;
	
};
