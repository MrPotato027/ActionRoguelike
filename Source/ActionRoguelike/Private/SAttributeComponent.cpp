// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"
#include <SGameModeBase.h>
#include <Net/UnrealNetwork.h>


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);



// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	HealthMax = 100;
	Health = HealthMax;

	RageMax = 100;
	Rage = 0;

	SetIsReplicatedByDefault(true);
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::IsHealthAtMax() const
{
	return Health == HealthMax;
}

float USAttributeComponent::GetActualPercentHealth() const
{
	return Health / HealthMax;
}

bool USAttributeComponent::SpendRage(float Amount)
{
	if (Amount <= Rage) {
		Rage -= Amount;
		return true;
	}

	return false;
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -HealthMax);
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f) {
		return false;
	}

	if (Delta < 0.0f) {
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		Delta *= DamageMultiplier;

		Rage = FMath::Clamp(Rage - Delta, 0.f, RageMax);
	}

	float oldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - oldHealth;
	//OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta, Rage);

	MulticastHealthChanged(InstigatorActor, Health, ActualDelta, Rage);

	//Died
	if (ActualDelta < 0.0f && Health == 0.0f) {
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if (GM) {
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return ActualDelta != 0;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor) {
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp) {
		return AttributeComp->IsAlive();
	}
	return false;
}

void USAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta, float NewRage)
{
	//OnHealthChanged.Broadcast(InstigatorActor, NewHealth, Delta);
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta, NewRage);
}

void USAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(USAttributeComponent, Health, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(USAttributeComponent, HealthMax, SharedParams);
	//DOREPLIFETIME_CONDITION(USAttributeComponent, HealthMax, COND_InitialOnly);

	DOREPLIFETIME_WITH_PARAMS_FAST(USAttributeComponent, Rage, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(USAttributeComponent, RageMax, SharedParams);
}

