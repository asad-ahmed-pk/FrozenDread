//
// BaseSaveGame.h
// Definition of the UBaseSaveGame class.
//

#pragma once

#include "CoreMinimal.h"
#include "EnhancedActionKeyMapping.h"
#include "GameFramework/SaveGame.h"

#include "BaseSaveGame.generated.h"

/**
 * The main save data for the game.
 */
UCLASS()
class FROZENDREAD_API UBaseSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category="Settings")
	TArray<FEnhancedActionKeyMapping> KeyMappings;
	
};
