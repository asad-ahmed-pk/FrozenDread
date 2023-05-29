//
// DataPad.cpp
// Implementation of the ADataPad class.
//

#include "DataPad.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ADataPad::ADataPad()
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
