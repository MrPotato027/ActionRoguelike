// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include <SGameplayFunctionLibrary.h>

void ASMagicProjectile::OnMagicHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		/*
		UE_LOG(LogTemp, Log, TEXT("Projectile Hit"));

		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			// minus in front of DamageAmount to apply the change as damage, not healing
			AttributeComp->ApplyHealthChange(GetInstigator(), -DamageAmount);

			UE_LOG(LogTemp, Log, TEXT("Projectile Apply Damage"));
		}

		Explode();
		*/

		if (USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, Hit)) {
			//Explode();
		}

		Explode();

		//ImpactAudioComp->Play();
		UGameplayStatics::PlaySoundAtLocation(this, ImpactAudioComp->Sound, GetActorLocation(), GetActorRotation(), 1.0f, 1.0f, 0.0f);
	}
}

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	SphereComp->SetSphereRadius(20.0f);
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	SphereComp->OnComponentHit.Clear();
	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnMagicHit);

	ImpactAudioComp = CreateDefaultSubobject<UAudioComponent>("ImpactAudioComp");
	ImpactAudioComp->bAutoActivate = false;
	ImpactAudioComp->SetupAttachment(SphereComp);

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


