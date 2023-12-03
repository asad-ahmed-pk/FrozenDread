//
// MainLevelCoordinator.cpp
// Implementation of the AMainLevelCoordinator class.
//

#include "FrozenDread/Level/MainLevelCoordinator.h"

#include "LevelSequence.h"
#include "Components/RectLightComponent.h"
#include "Engine/BlockingVolume.h"
#include "Engine/RectLight.h"
#include "Engine/TriggerVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/AmbientSound.h"

#include "FrozenDread/AI/PatrolWaypointSet.h"
#include "FrozenDread/Game/GameStatics.h"
#include "FrozenDread/Game/InventoryItemInfo.h"
#include "FrozenDread/Game/MusicData.h"
#include "FrozenDread/Gameplay/Door.h"
#include "FrozenDread/Gameplay/InteractionItem.h"
#include "FrozenDread/Level/LevelObjects.h"
#include "FrozenDread/Player/Inventory.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/System/GameEventSubsystem.h"
#include "FrozenDread/System/GameObjectiveSubsystem.h"
#include "FrozenDread/System/MusicPlayerSubsystem.h"
#include "FrozenDread/System/PlayerDialogueSubsystem.h"

void AMainLevelCoordinator::BeginPlay()
{
	Super::BeginPlay();
	SetupReferences();
}

void AMainLevelCoordinator::Init(const FSubsystemCache& SubsystemCacheRef)
{
	Super::Init(SubsystemCacheRef);

	// Subscribe to the game event sub-system's player chase event
	SubsystemCache.GameEventSubsystem->OnPlayerBeingChased.AddUObject(this, &AMainLevelCoordinator::UpdatePlayerChaseStatus);
}

void AMainLevelCoordinator::SetupReferences()
{
	// Cache the player
	Player = UGameStatics::GetPlayer(this);

	UWorld* World { GetWorld() };
	
	// Cache the reference for the door with the repair panel
	RepairPanelDoor = UGameStatics::GetActorInLevel<ADoor>(Tags::TAG_ACTOR_DOOR_REPAIR_PANEL, World);

	// Cache the reference for the red alert sequence
	RedAlertSound = UGameStatics::GetActorInLevel<AAmbientSound>(Tags::TAG_ACTOR_AMBIENT_SOUND_RED_ALERT, World);

	// Cache the reference for the red alert light
	RedAlertLight = UGameStatics::GetActorInLevel<ARectLight>(Tags::TAG_ACTOR_RECT_LIGHT_RED_ALERT, World);

	// Cache the reference for the exit trigger and blocking volumes
	ExitTriggerVolume = UGameStatics::GetActorInLevel<ATriggerVolume>(Tags::TAG_TRIGGER_EARLY_EXIT, World);
	ExitBlockingVolume = UGameStatics::GetActorInLevel<ABlockingVolume>(Tags::TAG_ACTOR_EXIT_BLOCKING_VOLUME, World);
	EscapeTriggerVolume = UGameStatics::GetActorInLevel<ATriggerVolume>(Tags::TAG_TRIGGER_ESCAPE, World);

	// Flashlight trigger volume
	FlashLightDialogueTriggerVolume = UGameStatics::GetActorInLevel<ATriggerVolume>(Tags::TAG_TRIGGER_FLASHLIGHT_DIALOGUE, World);

	// Setup the monster spawns
	SetupMonsterSpawns();
}

void AMainLevelCoordinator::SetupMonsterSpawns()
{
	UWorld* World { GetWorld() };
	
	// Monster 1
	const FVector Monster1Location { UGameStatics::GetActorInLevel<AActor>(Tags::TAG_MONSTER_1_SPAWN_LOCATION, World)->GetActorLocation() };
	APatrolWaypointSet* Monster1Waypoints { UGameStatics::GetActorInLevel<APatrolWaypointSet>(Tags::TAG_MONSTER_1_Waypoints, World) };

	// Monster 2
	const FVector Monster2Location { UGameStatics::GetActorInLevel<AActor>(Tags::TAG_MONSTER_2_SPAWN_LOCATION, World)->GetActorLocation() };
	APatrolWaypointSet* Monster2Waypoints { UGameStatics::GetActorInLevel<APatrolWaypointSet>(Tags::TAG_MONSTER_2_Waypoints, World) };

	MonsterSpawnInfoList.Add({ Monster1Location, Monster1Waypoints });
	MonsterSpawnInfoList.Add({ Monster2Location, Monster2Waypoints });
}

void AMainLevelCoordinator::StartLevel()
{
	// Add main objective and primary objective
	AddObjectiveOnce(MainObjective);
	AddObjectiveOnce(OverrideLockDownObjective);

	// Play intro music
	SubsystemCache.MusicPlayerSubsystem->PlayRandomTrack(EMusicTrackType::Intro);
}

void AMainLevelCoordinator::PlayerIntroSequenceCompleted()
{
	// Show the intro dialogue
	check(!IntroDialogueOptions.IsEmpty());
	PlayDialogue(IntroDialogueOptions);
}

void AMainLevelCoordinator::TriggerGameOver()
{
	check(GameOverLevelSequence);
	PlayLevelSequence(GameOverLevelSequence, [&](ULevelSequence* Sequence){
		if (Sequence == GameOverLevelSequence)
		{
			SubsystemCache.GameEventSubsystem->DeathLevelSequenceFinished();
		}
	});
}

void AMainLevelCoordinator::PlayerInteractedWithDoor(uint8 DoorID, EDoorLockState DoorLockState)
{
	// If any of the doors is the control room door
	switch (static_cast<EInteractionItemID>(DoorID))
	{
	case EInteractionItemID::ControlRoomDoor:
		{
			// If door is locked with keycard, play locked dialogue item at random
			if (DoorLockState == EDoorLockState::RequiresKeyCard)
			{
				check(SubsystemCache.DialogueSubsystem);
				const int32 Index { FMath::RandRange(0, LockedDoorDialogueOptions.Num() - 1) };
				const FDialogueItem* DialogueItem { LockedDoorDialogueOptions[Index].GetRow<FDialogueItem>(TEXT("MainLevelCoordinator::PlayerInteractedWithDoor")) };
				SubsystemCache.DialogueSubsystem->AddDialogueItem(*DialogueItem, {});

				// Play the dialogue if the goal has not been added yet
				const FGameObjective* KeyCardGoal { FindKeyCardObjective.GetRow<FGameObjective>("AMainLevelCoordinator::PlayerInteractedWithDoor") };
				if (!SubsystemCache.GameObjectiveSubsystem->IsObjectiveAdded(*KeyCardGoal))
				{
					check(FindKeyCardGoalDialogueOptions.Num() > 0);

					const TFunction<void()> CallBackFunc = [this](){
						// Add objective for keycard
						AddObjectiveOnce(FindKeyCardObjective);
					};
					
					PlayDialogue(FindKeyCardGoalDialogueOptions, CallBackFunc);
				}
			}

			break;
		}

	case EInteractionItemID::BrokenDoor:
		{
			// Door is still locked (panel not repaired)
			if (DoorLockState == EDoorLockState::Locked)
			{
				PlayDialogue(BrokenPanelDialogueOptions);
				AddObjectiveOnce(DoorRepairObjective);
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

void AMainLevelCoordinator::PlayDialogue(const TArray<FDataTableRowHandle>& DialogueRowHandles, const TOptional<TFunction<void()>>& CallBackFunc) const
{
	for (const FDataTableRowHandle& RowHandle : DialogueRowHandles)
	{
		check(SubsystemCache.DialogueSubsystem);
		const FDialogueItem* DialogueItem { RowHandle.GetRow<FDialogueItem>(TEXT("AMainLevelCoordinator::PlayDialogue")) };
		SubsystemCache.DialogueSubsystem->AddDialogueItem(*DialogueItem, CallBackFunc);
	}
}

void AMainLevelCoordinator::PlayInteractionSoundAtLocation(USoundBase* Sound, const FVector& Location) const
{
	check(Sound);
	check(ItemInteractionSoundAttenuation);
	UGameplayStatics::PlaySoundAtLocation(this, Sound, Location, FRotator::ZeroRotator);
}

void AMainLevelCoordinator::SpawnMonster(int32 Index)
{
	check(Index < MonsterSpawnInfoList.Num());
	check(MonsterClass);
	const FMonsterSpawnInfo& SpawnInfo { MonsterSpawnInfoList[Index] };
	SubsystemCache.GameEventSubsystem->SpawnMonster(MonsterClass, SpawnInfo.SpawnLocation, SpawnInfo.Waypoints.Get());
}

void AMainLevelCoordinator::UpdatePlayerChaseStatus(bool IsChased) const
{
	SubsystemCache.MusicPlayerSubsystem->PlayRandomTrack(IsChased ? EMusicTrackType::MonsterChase : EMusicTrackType::Gameplay);
}

void AMainLevelCoordinator::AddObjectiveOnce(const FDataTableRowHandle& RowHandle) const
{
	check(!RowHandle.IsNull());
	const FGameObjective* Objective { RowHandle.GetRow<FGameObjective>("AMainLevelCoordinator::AddObjective") };
	if (!SubsystemCache.GameObjectiveSubsystem->IsObjectiveAdded(*Objective))
	{
		SubsystemCache.GameObjectiveSubsystem->AddObjective(*Objective);
	}
}

void AMainLevelCoordinator::MarkObjectiveCompleted(const FDataTableRowHandle& RowHandle) const
{
	check(!RowHandle.IsNull());
	const FGameObjective* Objective { RowHandle.GetRow<FGameObjective>("AMainLevelCoordinator::MarkObjectiveCompleted") };
	if (SubsystemCache.GameObjectiveSubsystem->IsObjectiveAdded(*Objective))
	{
		SubsystemCache.GameObjectiveSubsystem->CompleteObjective(*Objective);
	}
}

void AMainLevelCoordinator::AddKeyCardGoal()
{
	check(!FindKeyCardObjective.IsNull());
	AddObjectiveOnce(FindKeyCardObjective);
}

void AMainLevelCoordinator::OnTriggerVolumeBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// Ensure that it is the player that is overlapping with the trigger volume
	if (!Cast<APlayerCharacter>(OtherActor))
	{
		return;
	}

	ATriggerVolume* TriggerVolume { CastChecked<ATriggerVolume>(OverlappedActor) };

	// Red alert trigger volume
	if (TriggerVolume->ActorHasTag(Tags::TAG_TRIGGER_RED_ALERT))
	{
		check(Player.IsValid());
		check(!InventoryItemToRepairDoor.IsNull());
		const uint8 ItemID { InventoryItemToRepairDoor.GetRow<FInventoryItemInfo>("AMainLevelCoordinator::OnTriggerVolumeBeginOverlap")->ID };
		if (Player->GetInventory()->HasItem(ItemID))
		{
			TriggerVolume->Destroy();

			// Camera shake and sound for impact
			check(RedAlertCameraShakeClass);
			check(RedAlertImpactSound);
			UGameplayStatics::PlaySound2D(this, RedAlertImpactSound);
			Player->GetController<APlayerController>()->ClientStartCameraShake(RedAlertCameraShakeClass);

			// Start red alert sequence after 2 seconds
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this]
			{
				// Play the red alert alarm
				RedAlertSound->Play();
				RedAlertLight->RectLightComponent->SetVisibility(true, true);

				// Spawn the first monster
				SpawnMonster(0);
			}), 2.0F, false);
		}
	}
	else if (TriggerVolume->ActorHasTag(Tags::TAG_TRIGGER_2ND_MONSTER_SPAWN))
	{
		// Spawn the 2nd monster if player has picked up keycard
		check(Player.IsValid());
		check(!InventoryItemToUnlockControlRoom.IsNull());
		const uint8 ItemID { InventoryItemToUnlockControlRoom.GetRow<FInventoryItemInfo>("AMainLevelCoordinator::OnTriggerVolumeBeginOverlap")->ID };
		
		if (Player->GetInventory()->HasItem(ItemID))
		{
			SpawnMonster(1);
			TriggerVolume->Destroy();
		}
	}
	else if (TriggerVolume->ActorHasTag(Tags::TAG_TRIGGER_EARLY_EXIT))
	{
		check(EarlyExitDialogueOptions.Num() > 0);
		PlayDialogue(EarlyExitDialogueOptions);
	}
	else if (TriggerVolume->ActorHasTag(Tags::TAG_TRIGGER_FLASHLIGHT_DIALOGUE))
	{
		check(FlashLightDialogueOptions.Num() > 0);
		PlayDialogue(FlashLightDialogueOptions);
		TriggerVolume->Destroy();
	}
	else if (TriggerVolume->ActorHasTag(Tags::TAG_TRIGGER_ESCAPE))
	{
		check(Player.IsValid());
		const AGamePlayerController* PlayerController { Player->GetController<AGamePlayerController>() };
		PlayerController->StartGameCompleteSequence();
	}
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

				// Complete the objective
				MarkObjectiveCompleted(DoorRepairObjective);
			}
			else
			{
				PlayDialogue(BrokenPanelDialogueOptions);
				AddObjectiveOnce(DoorRepairObjective);
			}

			break;
		}

	case EInteractionItemID::ControlRoomPanel:
		{
			// Complete the objective
			MarkObjectiveCompleted(OverrideLockDownObjective);

			// Remove the blocking and trigger volume so player can exit
			check(ExitBlockingVolume.IsValid());
			ExitBlockingVolume->Destroy();
			check(ExitTriggerVolume.IsValid());
			ExitTriggerVolume->Destroy();

			// Play dialogue after 2 seconds
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this]
			{
				check(!LiftedLockDownDialogueOptions.IsEmpty());
				PlayDialogue(LiftedLockDownDialogueOptions);
			}), 2.0F, false);
			
			break;
		}

		default:
			break;
	}
}

void AMainLevelCoordinator::PlayerPickedUpItem(EInventoryItemID ItemID)
{
	switch (ItemID)
	{
	case EInventoryItemID::ControlRoomKeyCard:
		check(!PickedUpKeyCardDialogueOptions.IsEmpty());
		MarkObjectiveCompleted(FindKeyCardObjective);
		PlayDialogue(PickedUpKeyCardDialogueOptions);
		break;

	default:
		break;
	}
}

