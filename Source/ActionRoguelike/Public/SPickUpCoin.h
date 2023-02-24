// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickUpItem.h"
#include "SPickUpCoin.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPickUpCoin : public ASPickUpItem
{
	GENERATED_BODY()

public:
	ASPickUpCoin();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	float AmountToAdd;
	
};
