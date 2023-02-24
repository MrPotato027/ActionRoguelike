// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUpItem.h"

// Sets default values
ASPickUpItem::ASPickUpItem()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	ActiveDelay = 10.0f;
	bIsActive = true;
}

void ASPickUpItem::Interact_Implementation(APawn* InstigatorPawn)
{

}

void ASPickUpItem::Active_TimeElapsed()
{
	Mesh->SetVisibility(true);
	//Mesh->SetRelativeScale3D(FVector(1.0f));
	bIsActive = true;
}

void ASPickUpItem::Deactive()
{
	Mesh->SetVisibility(false);
	//Mesh->SetRelativeScale3D(FVector(1.0f));
	bIsActive = false;
}


