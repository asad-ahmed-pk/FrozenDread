﻿//
// LevelCoordinator.h
// Definition of the ALevelCoordinator class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "LevelCoordinator.generated.h"

class AInteractionItem;
enum class EDoorLockState : uint8;

class UPlayerDialogueSubsystem;
class UGameEventSubsystem;
class UMusicPlayerSubsystem;
class UGameObjectiveSubsystem;

/** The collection of sub-systems cached for use for each level coordinator */
struct FSubsystemCache
{
	UGameEventSubsystem* GameEventSubsystem;
	UGameObjectiveSubsystem* GameObjectiveSubsystem;
	UPlayerDialogueSubsystem* DialogueSubsystem;
	UMusicPlayerSubsystem* MusicPlayerSubsystem;
};

/*
 * Base coordinator class that coordinates level events and progressions through the use of sub-systems.
 */
UCLASS()
class FROZENDREAD_API ALevelCoordinator : public AInfo
{
	GENERATED_BODY()

public:
	/** Init this coordinator with the subsystems cache */
	virtual void Init(const FSubsystemCache& SubsystemCacheRef);
	
	/** The player interacted with a door in the level */
	virtual void PlayerInteractedWithDoor(uint8 DoorID, EDoorLockState DoorLockState);

	/** The player interacted with an interactive item in the level */
	virtual void PlayerInteractedWithItem(uint8 ItemID, AInteractionItem* Item);

protected:
	FSubsystemCache SubsystemCache;
};


