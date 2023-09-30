//
// GameStatics.h
// Definition of the UGameStatics class.
//

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

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

	/** Get a reference to the actor of the given type and unique tag. */
	template<typename ActorClass>
	static ActorClass* GetActorInLevel(const char* Tag, UWorld* World)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsWithTag(World, { Tag }, Actors);
		check(Actors.Num() == 1);
		return Cast<ActorClass>(Actors[0]);
	}
};
