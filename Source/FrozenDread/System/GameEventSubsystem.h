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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerChaseStatusDelegate, bool, IsChased);

/**
 * Subsystem responsible for handling key events and triggers in the game.
 */
UCLASS()
class FROZENDREAD_API UGameEventSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Init
	void Setup(APlayerCharacter* PlayerCharacter, AMonster* MonsterCharacter);

	// The player was caught by the monster
	void PlayerWasCaught() const;

	// The player requested to restart the level
	void PlayerRequestedRestart() const;

	// The player requested to quit the level and go back to the main menu
	void PlayerRequestedLevelQuit() const;

	// A monster is chasing the player
	void PlayerIsBeingChased(bool IsChased) const;

public:
	UPROPERTY(BlueprintAssignable, Category="Game Events")
	FPlayerChaseStatusDelegate OnPlayerBeingChased;

public:
	// To be called when the death level sequence is completed
	UFUNCTION(BlueprintCallable, Category="Level Events")
	void DeathLevelSequenceFinished();

	// Enable or disable the player's input
	UFUNCTION(BlueprintCallable, Category="Utility")
	void SetPlayerInputEnabled(bool IsEnabled);

private:
	TWeakObjectPtr<APlayerCharacter> Player;
	TWeakObjectPtr<AMonster> Monster;

	bool IsMonsterChasingPlayer { false };
};
