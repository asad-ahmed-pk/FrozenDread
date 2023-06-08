//
// Monster.h
// Definition of the AMonster class.
//

#include "Monster.h"

#include "Components/CapsuleComponent.h"


// Sets default values
AMonster::AMonster()
{
	// Capsule setup
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Other settings
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

