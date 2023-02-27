// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemHealthPotion.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

// Sets default values
ASItemHealthPotion::ASItemHealthPotion()
{
	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	//RootComponent = Mesh;

	AmountToHeal = 50.0f;
	//ActiveDelay = 10.0f;
	//bIsActive = true;
}

void ASItemHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!bIsActive) return;

	if (InstigatorPawn) {
		ASPlayerState* PlayerState = Cast<ASPlayerState>(InstigatorPawn->GetPlayerState());
		if (PlayerState && PlayerState->GetCredits() > 0) {
			PlayerState->AddCredits(-1);

			USAttributeComponent* AttributeComp = InstigatorPawn->FindComponentByClass<USAttributeComponent>();
			if (AttributeComp) {
				if (AttributeComp->IsHealthAtMax()) return;

				//Mesh->SetVisibility(false);
				AttributeComp->ApplyHealthChange(this, AmountToHeal);
				//bIsActive = false;
				Deactive();
				GetWorldTimerManager().SetTimer(TimerHandle_PickUpItem, this, &ASItemHealthPotion::Active_TimeElapsed, ActiveDelay);
			}
		}
	}
	
}

FText ASItemHealthPotion::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = InstigatorPawn->FindComponentByClass<USAttributeComponent>();
	if (AttributeComp && AttributeComp->IsHealthAtMax()) {
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health.");
	}

	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits. Restores health to maximum."), -1);
}

/*
void ASItemHealthPotion::Active_TimeElapsed()
{
	Mesh->SetVisibility(true);
	Mesh->SetRelativeScale3D(FVector(1.0f));
	bIsActive = true;
}
*/

#undef LOCTEXT_NAMESPACE
