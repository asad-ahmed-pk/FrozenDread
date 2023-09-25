//
// GameStatics.h
// Definition of the UGameStatics class.
//

#pragma once

#include "CoreMinimal.h"

class AGameLevelScriptActor;
class UBlackboardComponent;
class UMusicPlayerSubsystem;
class UPlayerDialogueSubsystem;
class UGameEventSubsystem;
class APlayerCharacter;

/**
 * Static class for static helper functions
 */
class FROZENDREAD_API UGameStatics
{
public:
	/** Get a reference to the level script actor */
	static AGameLevelScriptActor* GetLevelScript(const AActor* ContextActor);

	/** Get the given blackboard for the AI pawn */
	static UBlackboardComponent* GetCharacterBlackBoardComponent(const APawn* Pawn);

	/** Get a reference to the Music Subsystem */
	static UMusicPlayerSubsystem* GetMusicSubsystem(const AActor* ContextActor);

	/** Get a reference the player character */
	static APlayerCharacter* GetPlayer(const AActor* ContextActor);
};
