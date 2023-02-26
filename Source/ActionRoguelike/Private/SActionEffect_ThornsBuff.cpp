// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionEffect_ThornsBuff.h"
#include "SAttributeComponent.h"
#include "SActionComponent.h"
#include "SGameplayFunctionLibrary.h"

USActionEffect_ThornsBuff::USActionEffect_ThornsBuff()
{
	ReflectFraction = 0.2f;

	Duration = 0.f;
	Period = 0.f;
	//bAutoStart = true;
}

void USActionEffect_ThornsBuff::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	USAttributeComponent* Attributes = USAttributeComponent::GetAttributes(GetOwningComponent()->GetOwner());
	if (Attributes) {
		Attributes->OnHealthChanged.AddDynamic(this, &USActionEffect_ThornsBuff::OnHealthChanged);
	}
}

void USActionEffect_ThornsBuff::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	USAttributeComponent* Attributes = USAttributeComponent::GetAttributes(GetOwningComponent()->GetOwner());
	if (Attributes) {
		Attributes->OnHealthChanged.RemoveDynamic(this, &USActionEffect_ThornsBuff::OnHealthChanged);
	}
}

void USActionEffect_ThornsBuff::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta, float NewRage)
{
	AActor* OwningActor = GetOwningComponent()->GetOwner();

	if (Delta < 0.0f && OwningActor != InstigatorActor) {
		int32 ReflectedAmount = FMath::RoundToInt(Delta * ReflectFraction);
		if (ReflectedAmount == 0) {
			return;
		}

		ReflectedAmount = FMath::Abs(ReflectedAmount);

		USGameplayFunctionLibrary::ApplyDamage(OwningActor, InstigatorActor, ReflectedAmount);
	}
}

