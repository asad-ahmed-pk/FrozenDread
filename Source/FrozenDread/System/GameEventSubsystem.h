//
// GameEventSubsystem.h
// Definition of the UGameEventSubsystem class.
//

#pragma once

#include "CoreMinimal.h"
#include "FrozenDread/AI/Monster.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameEventSubsystem.generated.h"

class APlayerCharacter;
class AMonster;
class APatrolWaypointSet;

enum class EDoorLockState : uint8;

DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerChaseStatusDelegate, bool);

/**
 * Subsystem responsible for handling key events and triggers in the game.
 */
UCLASS()
class FROZENDREAD_API UGameEventSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Init
	void Setup(APlayerCharacter* PlayerCharacter);

	// The player was caught by the monster
	void PlayerWasCaught() const;

	// The player requested to restart the level
	void PlayerRequestedRestart() const;

	// The player requested to quit the level and go back to the main menu
	void PlayerRequestedLevelQuit() const;

	// A monster is chasing the player
	void PlayerIsBeingChased(bool IsChased);

public:
	FPlayerChaseStatusDelegate OnPlayerBeingChased;

public:
	// To be called when the death level sequence is completed
	UFUNCTION(BlueprintCallable, Category="Level Events")
	void DeathLevelSequenceFinished();

	// Enable or disable the player's input
	UFUNCTION(BlueprintCallable, Category="Utility")
	void SetPlayerInputEnabled(bool IsEnabled);

	// Spawn a monster at the given location
	UFUNCTION(BlueprintCallable, Category="Level Events")
	void SpawnMonster(TSubclassOf<AMonster> MonsterClass, const FVector& Location, APatrolWaypointSet* WaypointSet = nullptr);


private:
	TWeakObjectPtr<APlayerCharacter> Player;
	TArray<TWeakObjectPtr<AMonster>> Monsters;
	bool IsMonsterChasingPlayer { false };
};
