// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName("PhysicsActor");
	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnCompHit);
	RootComponent = MeshComp;

	RadForceComp = CreateDefaultSubobject<URadialForceComponent>("RadForceComp");
	RadForceComp->Radius = 700;
	RadForceComp->ImpulseStrength = 2000;
	RadForceComp->bImpulseVelChange = true;
	RadForceComp->bAutoActivate = false;
	RadForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	RadForceComp->SetupAttachment(MeshComp);
}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnCompHit);
}

void ASExplosiveBarrel::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor) return;

	RadForceComp->FireImpulse();

	USAttributeComponent* AttributeComp = OtherActor->FindComponentByClass<USAttributeComponent>();
	if (AttributeComp) {
		AttributeComp->ApplyHealthChange(this, -50.0f);
	}

	UE_LOG(LogTemp, Log, TEXT("OnCompHit in Explosive Barrel"));

	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}



