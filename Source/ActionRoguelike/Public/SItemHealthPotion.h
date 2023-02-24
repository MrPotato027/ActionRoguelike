// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPickUpItem.h"
#include "SItemHealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASItemHealthPotion : public ASPickUpItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASItemHealthPotion();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditDefaultsOnly)
	float AmountToHeal;

	//UPROPERTY(EditDefaultsOnly)
	//float ActiveDelay;

	//bool bIsActive;

	//FTimerHandle TimerHandle_HealthPot;

	//UFUNCTION()
	//void Active_TimeElapsed();

};
