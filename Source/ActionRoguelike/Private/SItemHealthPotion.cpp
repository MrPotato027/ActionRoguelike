// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemHealthPotion.h"
#include "SAttributeComponent.h"

// Sets default values
ASItemHealthPotion::ASItemHealthPotion()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	AmountToHeal = 50.0f;
	ActiveDelay = 10.0f;
	bIsActive = true;
}

void ASItemHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!bIsActive) return;

	if (InstigatorPawn) {
		USAttributeComponent* AttributeComp = InstigatorPawn->FindComponentByClass<USAttributeComponent>();
		if (AttributeComp) {
			if (AttributeComp->IsHealthAtMax()) return;

			Mesh->SetVisibility(false);
			AttributeComp->ApplyHealthChange(this, AmountToHeal);
			bIsActive = false;
			GetWorldTimerManager().SetTimer(TimerHandle_HealthPot, this, &ASItemHealthPotion::Active_TimeElapsed, ActiveDelay);
		}
	}
	
}

void ASItemHealthPotion::Active_TimeElapsed()
{
	Mesh->SetVisibility(true);
	Mesh->SetRelativeScale3D(FVector(1.0f));
	bIsActive = true;
}


