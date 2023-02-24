// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionEffect_ThornsBuff.h"
#include "SAttributeComponent.h"

USActionEffect_ThornsBuff::USActionEffect_ThornsBuff()
{
	Duration = 0.f;
	Period = 0.f;
	bAutoStart = true;
}

void USActionEffect_ThornsBuff::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
}

void USActionEffect_ThornsBuff::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
}

void USActionEffect_ThornsBuff::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(Instigator->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp) {
		AttributeComp->ApplyHealthChange(Instigator, -20.f);
	}
}
