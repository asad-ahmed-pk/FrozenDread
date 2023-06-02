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
	UFUNCTION(BlueprintCallable)
	void PlayIntroCutScene();

	UFUNCTION(BlueprintCallable)
	void PlayEndingCutScene();
};
