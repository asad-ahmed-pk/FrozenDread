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
	
	// The player has interacted with the exo suit
	void PlayerInteractedWithExoSuit(const APlayerCharacter* PlayerCharacter);

	// The player was caught by the monster
	void PlayerWasCaught() const;

public:
	// To be called when the death level sequence is completed
	UFUNCTION(BlueprintCallable, Category="Level Events")
	void DeathLevelSequenceFinished();

private:
	TWeakObjectPtr<APlayerCharacter> Player;
	TWeakObjectPtr<AMonster> Monster;
	bool PlayerIsWearingExoSuit { false };
};
