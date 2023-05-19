//
// Door.cpp
// Implementation of the ADoor class.
//

#include "Door.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
	// Root component
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComponent;
	
	// Create the collision mesh for the interaction
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	InteractionBox->SetupAttachment(RootComponent);
	
	// Create the mesh
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMesh->SetupAttachment(RootComponent);

	// Other settings
	PrimaryActorTick.bCanEverTick = false;
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/////////////////////////////////////////// IInteractiveObject Interface ///////////////////////////////////////////

void ADoor::Interact(APlayerCharacter* PlayerCharacter)
{
	if (!CanInteract)
	{
		return;
	}
	
	switch (LockState)
	{
	case EDoorLockState::Unlocked:
		DoorInteractionEvent.Broadcast();
		break;

	case EDoorLockState::Locked:
		// Access denied
		check(AccessDeniedSound);
		UGameplayStatics::PlaySoundAtLocation(this, AccessDeniedSound, GetActorLocation());
		break;

	case EDoorLockState::RequiresKeyCard:
		// TODO: Query player's inventory system and unlock if matching keycard is available
		break;
	}

	// Start the cooldown timer so the player cannot interact for some time
	CanInteract = false;
	GetWorldTimerManager().SetTimer(CoolDownTimer, this, &ADoor::CoolDownComplete, CoolDownTimeSeconds, false);
}

void ADoor::SetHighlighted(bool IsHighlighted)
{
	
}

FText ADoor::DisplayText() const
{
	if (IsOpen)
	{
		return OpenStateText;
	}
	else
	{
		return ClosedStateText;
	}
}
