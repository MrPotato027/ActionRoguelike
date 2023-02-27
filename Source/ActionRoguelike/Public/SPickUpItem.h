// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPickUpItem.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASPickUpItem : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPickUpItem();

	virtual void Interact_Implementation(APawn* InstigatorPawn);
	FText GetInteractText_Implementation(APawn* InstigatorPawn);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	FTimerHandle TimerHandle_PickUpItem;

	UPROPERTY(EditDefaultsOnly)
	float ActiveDelay;

	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
	bool bIsActive;

	UFUNCTION()
	void Active_TimeElapsed();

	void Deactive();

	UFUNCTION()
	void OnRep_IsActive();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

};
