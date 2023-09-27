//
// MainLevelCoordinator.h
// Definition of the AMainLevelCoordinator class.
//

#pragma once

#include "CoreMinimal.h"
#include "LevelCoordinator.h"
#include "FrozenDread/Game/Dialogue.h"

#include "MainLevelCoordinator.generated.h"

class ADoor;
class APlayerCharacter;
class USoundBase;
class USoundAttenuation;
class UPlayerDialogueSubsystem;

/**
 * The level coordinator for the main level.
 */
UCLASS(BlueprintType, Blueprintable)
class FROZENDREAD_API AMainLevelCoordinator : public ALevelCoordinator
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	
	/** The player interacted with a door in the level */
	virtual void PlayerInteractedWithDoor(uint8 DoorID, EDoorLockState DoorLockState) override;

	/** The player interacted with the given item */
	virtual void PlayerInteractedWithItem(uint8 ItemID, AInteractionItem* Item) override;

private:
	void SetupReferences();
	void PlayDialogue(const TArray<FDataTableRowHandle>& DialogueRowHandles) const;
	void PlayInteractionSoundAtLocation(USoundBase* Sound, const FVector& Location) const;
	

private:
	/** The list of dialogue items that the player can say when interacting with a locked door */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RequiredAssetDataTags="RowStructure=/Script/FrozenDread.DialogueItem"))
	TArray<FDataTableRowHandle> LockedDoorDialogueOptions;

	/** The list of dialogue item to play when interacting with the broken door panel */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RequiredAssetDataTags="RowStructure=/Script/FrozenDread.DialogueItem"))
	TArray<FDataTableRowHandle> BrokenPanelDialogueOptions;

	/** The inventory item that the player is expected to have for repairing the broken door */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true", RequiredAssetDataTags="RowStructure=/Script/FrozenDread.InventoryItemInfo"))
	FDataTableRowHandle InventoryItemToRepairDoor;

	/** The sound to play when the player successfully repairs the damaged door panel */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundBase> DoorRepairSound;

	/** The sound attenuation settings to use when the player interacts with an item in the world */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundAttenuation> ItemInteractionSoundAttenuation;

private:
	TWeakObjectPtr<APlayerCharacter> Player;
	TWeakObjectPtr<ADoor> RepairPanelDoor;
};
