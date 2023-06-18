//
// GameLevelScriptActor.h
// Definition of the AGameLevelScriptActor class.
//

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class FROZENDREAD_API AGameLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	// Trigger game over since player was caught
	UFUNCTION(BlueprintNativeEvent)
	void PlayerWasCaught();
};
