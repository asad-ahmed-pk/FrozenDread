//
// GameStatics.h
// Definition of the UGameStatics class.
//

#pragma once

#include "CoreMinimal.h"

class AGameLevelScriptActor;

/**
 * Static class for static helper functions
 */
class FROZENDREAD_API UGameStatics
{
public:
	/** Get a reference to the level script actor */
	static AGameLevelScriptActor* GetLevelScript(const AActor* ContextActor);
};
