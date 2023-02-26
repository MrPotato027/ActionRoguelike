// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionEffect.h"
#include "SActionEffect_ThornsBuff.generated.h"

class USAttributeComponent;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USActionEffect_ThornsBuff : public USActionEffect
{
	GENERATED_BODY()

protected:
	float ReflectFraction;

public:
	USActionEffect_ThornsBuff();

	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;

	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta, float NewRage);
	
};
