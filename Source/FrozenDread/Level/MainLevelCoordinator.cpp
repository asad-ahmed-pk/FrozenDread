//
// MainLevelCoordinator.cpp
// Implementation of the AMainLevelCoordinator class.
//

#include "FrozenDread/Level/MainLevelCoordinator.h"

#include "Components/RectLightComponent.h"
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
#include "FrozenDread/System/MusicPlayerSubsystem.h"
#include "FrozenDread/System/PlayerDialogueSubsystem.h"


constexpr char* ACTOR_TAG_DOOR_WITH_REPAIR_PANEL { "BrokenPanelDoor" };

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
	
	// Cache the reference for the door with the repair panel
	RepairPanelDoor = UGameStatics::GetActorInLevel<ADoor>(ACTOR_TAG_DOOR_WITH_REPAIR_PANEL, GetWorld());

	// Cache the reference for the red alert sequence
	RedAlertSound = UGameStatics::GetActorInLevel<AAmbientSound>(Tags::TAG_ACTOR_AMBIENT_SOUND_RED_ALERT, GetWorld());

	// Cache the reference for the red alert light
	RedAlertLight = UGameStatics::GetActorInLevel<ARectLight>(Tags::TAG_ACTOR_RECT_LIGHT_RED_ALERT, GetWorld());

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

void AMainLevelCoordinator::SpawnMonster(int32 Index)
{
	check(Index < MonsterSpawnInfoList.Num());
	check(MonsterClass);
	const FMonsterSpawnInfo& SpawnInfo { MonsterSpawnInfoList[0] };
	SubsystemCache.GameEventSubsystem->SpawnMonster(MonsterClass, SpawnInfo.SpawnLocation, SpawnInfo.Waypoints.Get());
}

void AMainLevelCoordinator::UpdatePlayerChaseStatus(bool IsChased) const
{
	SubsystemCache.MusicPlayerSubsystem->PlayRandomTrack(IsChased ? EMusicTrackType::MonsterChase : EMusicTrackType::Gameplay);
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
	else if (TriggerVolume->ActorHasTag(Tags::TAG_TRIGGER_MUSIC_START))
	{
		SubsystemCache.MusicPlayerSubsystem->PlayRandomTrack(EMusicTrackType::Gameplay);
	}
	else if (TriggerVolume->ActorHasTag(Tags::TAG_TRIGGER_EARLY_EXIT))
	{
		check(EarlyExitDialogueOptions.Num() > 0);
		PlayDialogue(EarlyExitDialogueOptions);
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


