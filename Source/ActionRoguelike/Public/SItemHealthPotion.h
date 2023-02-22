// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemHealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASItemHealthPotion : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASItemHealthPotion();

	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditDefaultsOnly)
	float AmountToHeal;

	UPROPERTY(EditDefaultsOnly)
	float ActiveDelay;

	bool bIsActive;

	FTimerHandle TimerHandle_HealthPot;

	UFUNCTION()
	void Active_TimeElapsed();

};
