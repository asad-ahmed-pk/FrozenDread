//
// MainLevelCoordinator.h
// Definition of the AMainLevelCoordinator class.
//

#pragma once

#include "CoreMinimal.h"

#include "FrozenDread/Level/LevelCoordinator.h"
#include "FrozenDread/Game/Dialogue.h"

#include "MainLevelCoordinator.generated.h"

class ATriggerVolume;
class ABlockingVolume;
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
	/** Called when the game begins */
	virtual void BeginPlay() override;

	/** Called when the game mode inits this level coordinator */
	virtual void Init(const FSubsystemCache& SubsystemCacheRef) override;
	
	/** The player interacted with a door in the level */
	virtual void PlayerInteractedWithDoor(uint8 DoorID, EDoorLockState DoorLockState) override;

	/** The player interacted with the given item */
	virtual void PlayerInteractedWithItem(uint8 ItemID, AInteractionItem* Item) override;

	/** Player picked up an inventory item */
	virtual void PlayerPickedUpItem(EInventoryItemID ItemID) override;

	/** The player intro sequence was completed */
	virtual void PlayerIntroSequenceCompleted() override;

	/** Game over */
	virtual void TriggerGameOver() override;
	
public:
	virtual void OnTriggerVolumeBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

private:
	void SetupReferences();
	void SetupMonsterSpawns();
	void StartLevel();
	void PlayDialogue(const TArray<FDataTableRowHandle>& DialogueRowHandles, const TOptional<TFunction<void()>>& CallBackFunc = NullOpt) const;
	void PlayInteractionSoundAtLocation(USoundBase* Sound, const FVector& Location) const;
	void SpawnMonster(int32 Index);
	void UpdatePlayerChaseStatus(bool IsChased) const;
	void AddObjectiveOnce(const FDataTableRowHandle& RowHandle) const;
	void MarkObjectiveCompleted(const FDataTableRowHandle& RowHandle) const;
	void AddKeyCardGoal();


private:
	/** The list of dialogue to play when the game starts after the intro */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RowType="DialogueItem"))
	TArray<FDataTableRowHandle> IntroDialogueOptions;

	/** The dialogue to play to notify the player about flashlight use */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RowType="DialogueItem"))
	TArray<FDataTableRowHandle> FlashLightDialogueOptions;
	
	/** The list of dialogue items that the player can say when interacting with a locked door */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RowType="DialogueItem"))
	TArray<FDataTableRowHandle> LockedDoorDialogueOptions;

	/** The list of dialogue items to play when interacting with the broken door panel */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RowType="DialogueItem"))
	TArray<FDataTableRowHandle> BrokenPanelDialogueOptions;

	/** The list of dialogue items to play when the player tries to exit the game early */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RowType="DialogueItem"))
	TArray<FDataTableRowHandle> EarlyExitDialogueOptions;

	/** The list of dialogue items to play to introduce the key card goal */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RowType="DialogueItem"))
	TArray<FDataTableRowHandle> FindKeyCardGoalDialogueOptions;

	/** The list of dialogue items to play when the player picks up the keycard */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RowType="DialogueItem"))
	TArray<FDataTableRowHandle> PickedUpKeyCardDialogueOptions;

	/** The list of dialogue items to play when the player lifts the lock-down */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue", meta=(AllowPrivateAccess="true", RowType="DialogueItem"))
	TArray<FDataTableRowHandle> LiftedLockDownDialogueOptions;

	/** The inventory item that the player is expected to have for repairing the broken door */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true", RowType="InventoryItemInfo"))
	FDataTableRowHandle InventoryItemToRepairDoor;

	/** The inventory item that the player is expected to have for accessing the control room */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true", RowType="InventoryItemInfo"))
	FDataTableRowHandle InventoryItemToUnlockControlRoom;

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

	/** The main top level objective to complete */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Objectives", meta=(AllowPrivateAccess="true", RowType="GameObjective"))
	FDataTableRowHandle MainObjective;

	/** The door repair objective */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Objectives", meta=(AllowPrivateAccess="true", RowType="GameObjective"))
	FDataTableRowHandle DoorRepairObjective;

	/** The key-card objective */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Objectives", meta=(AllowPrivateAccess="true", RowType="GameObjective"))
	FDataTableRowHandle FindKeyCardObjective;

	/** The override lockdown objective */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Objectives", meta=(AllowPrivateAccess="true", RowType="GameObjective"))
	FDataTableRowHandle OverrideLockDownObjective;

	/** The game over cut scene to play when the player is caught */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Cutscenes", meta=(AllowPrivateAccess="true"))
	TObjectPtr<ULevelSequence> GameOverLevelSequence;
	
private:
	TWeakObjectPtr<APlayerCharacter> Player;
	TWeakObjectPtr<ADoor> RepairPanelDoor;
	TWeakObjectPtr<AAmbientSound> RedAlertSound;
	TWeakObjectPtr<ARectLight> RedAlertLight;
	TWeakObjectPtr<ATriggerVolume> ExitTriggerVolume;
	TWeakObjectPtr<ABlockingVolume> ExitBlockingVolume;
	TWeakObjectPtr<ATriggerVolume> FlashLightDialogueTriggerVolume;
	TWeakObjectPtr<ATriggerVolume> EscapeTriggerVolume;

	TArray<FMonsterSpawnInfo> MonsterSpawnInfoList;

	FTimerHandle TimerHandle;
};
