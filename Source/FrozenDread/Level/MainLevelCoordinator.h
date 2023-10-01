//
// MainLevelCoordinator.h
// Definition of the AMainLevelCoordinator class.
//

#pragma once

#include "CoreMinimal.h"

#include "FrozenDread/Level/LevelCoordinator.h"
#include "FrozenDread/Game/Dialogue.h"

#include "MainLevelCoordinator.generated.h"

class AMonster;
class ARectLight;
class AAmbientSound;
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
	virtual void BeginPlay() override;
	
	/** The player interacted with a door in the level */
	virtual void PlayerInteractedWithDoor(uint8 DoorID, EDoorLockState DoorLockState) override;

	/** The player interacted with the given item */
	virtual void PlayerInteractedWithItem(uint8 ItemID, AInteractionItem* Item) override;
	
public:
	virtual void OnTriggerVolumeBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

private:
	void SetupReferences();
	void SetupMonsterSpawns();
	void PlayDialogue(const TArray<FDataTableRowHandle>& DialogueRowHandles) const;
	void PlayInteractionSoundAtLocation(USoundBase* Sound, const FVector& Location) const;
	void SpawnMonster(int32 Index);


private:
	/** The list of dialogue items that the player can say when interacting with a locked door */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RequiredAssetDataTags="RowStructure=/Script/FrozenDread.DialogueItem"))
	TArray<FDataTableRowHandle> LockedDoorDialogueOptions;

	/** The list of dialogue items to play when interacting with the broken door panel */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RequiredAssetDataTags="RowStructure=/Script/FrozenDread.DialogueItem"))
	TArray<FDataTableRowHandle> BrokenPanelDialogueOptions;

	/** The list of dialogue items to play when the player tries to exit the game early */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RequiredAssetDataTags="RowStructure=/Script/FrozenDread.DialogueItem"))
	TArray<FDataTableRowHandle> EarlyExitDialogueOptions;

	/** The inventory item that the player is expected to have for repairing the broken door */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true", RequiredAssetDataTags="RowStructure=/Script/FrozenDread.InventoryItemInfo"))
	FDataTableRowHandle InventoryItemToRepairDoor;

	/** The sound to play when the player successfully repairs the damaged door panel */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundBase> DoorRepairSound;

	/** The sound attenuation settings to use when the player interacts with an item in the world */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundAttenuation> ItemInteractionSoundAttenuation;

	/** The camera shake to play when the red alert is triggered */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UCameraShakeBase> RedAlertCameraShakeClass;

	/** The impact sound to play when the red alert is triggered */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundBase> RedAlertImpactSound;

	/** The monster class to use when spawning monsters */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	TSubclassOf<AMonster> MonsterClass;
	
private:
	TWeakObjectPtr<APlayerCharacter> Player;
	TWeakObjectPtr<ADoor> RepairPanelDoor;
	TWeakObjectPtr<AAmbientSound> RedAlertSound;
	TWeakObjectPtr<ARectLight> RedAlertLight;

	TArray<FMonsterSpawnInfo> MonsterSpawnInfoList;

	FTimerHandle TimerHandle;
};
