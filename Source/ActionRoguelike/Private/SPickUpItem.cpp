// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUpItem.h"
#include <Net/UnrealNetwork.h>

// Sets default values
ASPickUpItem::ASPickUpItem()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	ActiveDelay = 10.0f;
	bIsActive = true;

	SetReplicates(true);
}

void ASPickUpItem::Interact_Implementation(APawn* InstigatorPawn)
{

}

void ASPickUpItem::Active_TimeElapsed()
{
	//Mesh->SetVisibility(true);
	bIsActive = true;
	OnRep_IsActive();
}

void ASPickUpItem::Deactive()
{
	//Mesh->SetVisibility(false);
	bIsActive = false;
	OnRep_IsActive();
}

void ASPickUpItem::OnRep_IsActive()
{
	Mesh->SetVisibility(bIsActive);
}

void ASPickUpItem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ASPickUpItem, bIsActive, SharedParams);
}

