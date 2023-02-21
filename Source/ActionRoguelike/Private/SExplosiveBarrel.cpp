// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	RadForceComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExplosiveBarrel::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadForceComp->FireImpulse();
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

