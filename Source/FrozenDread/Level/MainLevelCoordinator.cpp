//
// MainLevelCoordinator.cpp
// Implementation of the AMainLevelCoordinator class.
//


#include "FrozenDread/Level/MainLevelCoordinator.h"

#include "FrozenDread/Game/GameStatics.h"
#include "FrozenDread/Game/InventoryItemInfo.h"
#include "FrozenDread/Gameplay/Door.h"
#include "FrozenDread/Level/LevelObjects.h"
#include "FrozenDread/Player/Inventory.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/System/PlayerDialogueSubsystem.h"

void AMainLevelCoordinator::BeginPlay()
{
	Super::BeginPlay();

	// Cache the player
	Player = UGameStatics::GetPlayer(this);
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

	case EInteractionItemID::BrokenDoorPanel:
		{
			// Check if player has the toolbox in the inventory
			check(Player.IsValid());
			check(!InventoryItemToRepairDoor.IsNull());

			const uint8 ItemID { InventoryItemToRepairDoor.GetRow<FInventoryItemInfo>(TEXT("MainLevelCoordinator::PlayerInteractedWithDoor"))->ID };
			if (Player->GetInventory()->HasItem(ItemID))
			{
				// TODO: Repair door event
			}
			else
			{
				PlayDialogue(BrokenPanelDialogueOptions);
			}
		}

	case EInteractionItemID::OtherDoor:
		// Nothing to do for other doors
		break;

		default:
			// All cases must be handled
			check(false);
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
