//
// GameLevelScriptActor.h
// Definition of the AGameLevelScriptActor class.
//

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevelScriptActor.generated.h"

class ADoor;

/**
 * Game level script
 */
UCLASS()
class FROZENDREAD_API AGameLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	// Trigger game over since player was caught
	UFUNCTION(BlueprintNativeEvent, Category="Player Events")
	void PlayerWasCaught();

	// An interactive item was interacted with by the player
	UFUNCTION(BlueprintNativeEvent, Category="Player Events")
	void PlayerInteractedWithItem(AActor* Actor);

	// The player tried to open a locked door
	UFUNCTION(BlueprintNativeEvent,Category="Player Events")
	void PlayerTriedLockedDoor(ADoor* Door);
};
