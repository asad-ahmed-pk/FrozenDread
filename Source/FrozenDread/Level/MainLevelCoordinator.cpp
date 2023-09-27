//
// MainLevelCoordinator.cpp
// Implementation of the AMainLevelCoordinator class.
//


#include "FrozenDread/Level/MainLevelCoordinator.h"

#include "FrozenDread/Game/GameStatics.h"
#include "FrozenDread/Game/InventoryItemInfo.h"
#include "FrozenDread/Gameplay/Door.h"
#include "FrozenDread/Gameplay/InteractionItem.h"
#include "FrozenDread/Level/LevelObjects.h"
#include "FrozenDread/Player/Inventory.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/System/PlayerDialogueSubsystem.h"
#include "Kismet/GameplayStatics.h"

constexpr char* ACTOR_TAG_DOOR_WITH_REPAIR_PANEL { "BrokenPanelDoor" };

void AMainLevelCoordinator::BeginPlay()
{
	Super::BeginPlay();
	SetupReferences();
}

void AMainLevelCoordinator::SetupReferences()
{
	// Cache the player
	Player = UGameStatics::GetPlayer(this);
	
	// Cache the reference for the door with the repair panel
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(this, { ACTOR_TAG_DOOR_WITH_REPAIR_PANEL }, Actors);
	check(Actors.Num() == 1);
	RepairPanelDoor = Cast<ADoor>(Actors[0]);
}

void AMainLevelCoordinator::PlayerInteractedWithDoor(uint8 DoorID, EDoorLockState DoorLockState)
{
	// If any of the doors is the control room door
	switch (static_cast<EInteractionItemID>(DoorID))
	{
	case EInteractionItemID::ControlRoomMainDoor:
	case EInteractionItemID::ControlRoomTopDoor:
	case EInteractionItemID::ControlRoomBottomDoor:
		{
			// If door is locked with keycard, play locked dialogue item at random
			if (DoorLockState == EDoorLockState::RequiresKeyCard)
			{
				check(SubsystemCache.DialogueSubsystem);
				const int32 Index { FMath::RandRange(0, LockedDoorDialogueOptions.Num()) };
				const FDialogueItem* DialogueItem { LockedDoorDialogueOptions[Index].GetRow<FDialogueItem>(TEXT("MainLevelCoordinator::PlayerInteractedWithDoor")) };
				SubsystemCache.DialogueSubsystem->AddDialogueItem(*DialogueItem, {});
			}

			break;
		}

	case EInteractionItemID::BrokenDoor:
		{
			// Door is still locked (panel not repaired)
			if (DoorLockState == EDoorLockState::Locked)
			{
				PlayDialogue(BrokenPanelDialogueOptions);
			}
			break;
		}

	case EInteractionItemID::OtherDoor:
		// Nothing to do for other doors
		break;

		default:
			// do nothing since not a door
			break;
	}
}

void AMainLevelCoordinator::PlayDialogue(const TArray<FDataTableRowHandle>& DialogueRowHandles) const
{
	for (const FDataTableRowHandle& RowHandle : DialogueRowHandles)
	{
		check(SubsystemCache.DialogueSubsystem);
		const FDialogueItem* DialogueItem { RowHandle.GetRow<FDialogueItem>(TEXT("AMainLevelCoordinator::PlayDialogue")) };
		SubsystemCache.DialogueSubsystem->AddDialogueItem(*DialogueItem, {});
	}
}

void AMainLevelCoordinator::PlayInteractionSoundAtLocation(USoundBase* Sound, const FVector& Location) const
{
	check(Sound);
	check(ItemInteractionSoundAttenuation);
	UGameplayStatics::PlaySoundAtLocation(this, Sound, Location, FRotator::ZeroRotator);
}

void AMainLevelCoordinator::PlayerInteractedWithItem(uint8 ItemID, AInteractionItem* Item)
{
	switch (static_cast<EInteractionItemID>(ItemID))
	{
	case EInteractionItemID::BrokenDoorPanel:
		{
			// Check if player has the toolbox in the inventory
			check(Player.IsValid());
			check(!InventoryItemToRepairDoor.IsNull());

			const uint8 InventoryItemID { InventoryItemToRepairDoor.GetRow<FInventoryItemInfo>(TEXT("MainLevelCoordinator::PlayerInteractedWithItem"))->ID };
			if (Player->GetInventory()->HasItem(InventoryItemID))
			{
				// Play the repair sound
				check(Item);
				PlayInteractionSoundAtLocation(DoorRepairSound, Item->GetActorLocation());
				Item->Destroy();

				// Unlock the repair panel door
				check(RepairPanelDoor.IsValid());
				RepairPanelDoor->Unlock();
			}
			else
			{
				PlayDialogue(BrokenPanelDialogueOptions);
			}
		}

		default:
			break;
	}
}


