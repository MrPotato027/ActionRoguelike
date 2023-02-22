// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"

void ASMagicProjectile::OnMagicHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UE_LOG(LogTemp, Log, TEXT("Projectile Hit"));

		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			// minus in front of DamageAmount to apply the change as damage, not healing
			AttributeComp->ApplyHealthChange(-DamageAmount);

			UE_LOG(LogTemp, Log, TEXT("Projectile Apply Damage"));
		}

		Explode();
	}
}

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	SphereComp->SetSphereRadius(20.0f);
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	SphereComp->OnComponentHit.Clear();
	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnMagicHit);

	DamageAmount = 20.0f;
}

/*
void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Projectile Overlap"));
	if (OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			// minus in front of DamageAmount to apply the change as damage, not healing
			AttributeComp->ApplyHealthChange(-DamageAmount);

			UE_LOG(LogTemp, Log, TEXT("Projectile Apply Damage"));

			// Only explode when we hit something valid
			Explode();
		}
	}
}
*/


