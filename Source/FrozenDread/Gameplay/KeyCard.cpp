//
// KeyCard.cpp
// Implementation of the AKeyCard class.
//

#include "KeyCard.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AKeyCard::AKeyCard()
{
	// Root scene component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	// Interaction Box
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	InteractionBox->SetupAttachment(RootComponent);
	
	// Other settings
	PrimaryActorTick.bCanEverTick = false;
}

