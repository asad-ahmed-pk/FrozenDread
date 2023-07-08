//
// Door.cpp
// Implementation of the ADoor class.
//

#include "Door.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

#include "FrozenDread/Player/Inventory.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/Game/GameStatics.h"
#include "FrozenDread/Gameplay/GameLevelScriptActor.h"
#include "FrozenDread/UI/DoorLockStatusWidget.h"

// Sets default values
ADoor::ADoor()
{
	// Root component
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComponent;
	
	// Create the collision mesh for the interaction
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	
	// Create the mesh
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);

	// World UMG widgets for the lock status
	LockStatusWidgetFront = CreateDefaultSubobject<UWidgetComponent>(TEXT("FrontLockStatusWidget"));
	LockStatusWidgetFront->SetupAttachment(DoorMesh);
	LockStatusWidgetBack = CreateDefaultSubobject<UWidgetComponent>(TEXT("BackLockStatusWidget"));
	LockStatusWidgetBack->SetupAttachment(DoorMesh);

	// Other settings
	PrimaryActorTick.bCanEverTick = false;
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	SetLockStatusWidgets(LockState != EDoorLockState::Unlocked);
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
		PlayerInteractedWithDoor();
		UGameStatics::GetLevelScript(this)->PlayerInteractedWithItem(this);
		break;

	case EDoorLockState::Locked:
		// Access denied
		check(AccessDeniedSound);
		UGameStatics::GetLevelScript(this)->PlayerTriedLockedDoor(this);
		UGameplayStatics::PlaySoundAtLocation(this, AccessDeniedSound, GetActorLocation());
		break;

	case EDoorLockState::RequiresKeyCard:
		// Query player's inventory system and unlock if matching key card is in the inventory
		if (PlayerHasKeyCard(PlayerCharacter))
		{
			check(UnlockSound);
			UGameplayStatics::PlaySoundAtLocation(this, UnlockSound, GetActorLocation());
			LockState = EDoorLockState::Unlocked;
			SetLockStatusWidgets(false);
		}
		else
		{
			UGameStatics::GetLevelScript(this)->PlayerTriedLockedDoor(this);
			UGameplayStatics::PlaySoundAtLocation(this, AccessDeniedSound, GetActorLocation());
		}
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

void ADoor::PlayerInteractedWithDoor_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Implement PlayerInteractedWithDoor() in BP"));
}

/////////////////////////////////////////// Door Functionality ///////////////////////////////////////////

// Check if the player has the key card for unlocking this door
bool ADoor::PlayerHasKeyCard(const APlayerCharacter* PlayerCharacter) const
{
	check(KeyCardID > 0);
	
	check(PlayerCharacter);

	const UInventory* Inventory { PlayerCharacter->GetInventory() };
	check(Inventory);

	return Inventory->HasItem(KeyCardID);
}

// Update the widget to show the locked the status
void ADoor::SetLockStatusWidgets(bool IsLocked) const
{
	UDoorLockStatusWidget* WidgetFront { CastChecked<UDoorLockStatusWidget>(LockStatusWidgetFront->GetWidget()) };
	WidgetFront->SetIsLocked(IsLocked);
	UDoorLockStatusWidget* WidgetBack { CastChecked<UDoorLockStatusWidget>(LockStatusWidgetBack->GetWidget()) };
	WidgetBack->SetIsLocked(IsLocked);
}

void ADoor::Unlock()
{
	LockState = EDoorLockState::Unlocked;
	SetLockStatusWidgets(false);
	check(UnlockSound);
	UGameplayStatics::PlaySoundAtLocation(this, UnlockSound, GetActorLocation());
}
