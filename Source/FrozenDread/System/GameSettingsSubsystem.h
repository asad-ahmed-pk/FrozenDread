//
// GameSettingsSubsystem.h
// Definition of the UGameInstanceSubsystem class.
//

#pragma once

#include "CoreMinimal.h"
#include "EnhancedActionKeyMapping.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "GameSettingsSubsystem.generated.h"

class UBaseSaveGame;
class APlayerCharacter;
class UPlayerMappableInputConfig;

/**
 * Subsystem responsible for managing game settings including key binds.
 */
UCLASS()
class FROZENDREAD_API UGameSettingsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Init this subsystem */
	void Init(UPlayerMappableInputConfig* PMIC);

	/** Returns the keymap from the save game or the default keymap if none is set */
	void GetKeyMappings(TArray<FEnhancedActionKeyMapping>& Mappings) const;

	/** Update and save the keymap settings */
	static void UpdateKeyMappings(const TArray<FEnhancedActionKeyMapping>& Mappings);

private:
	/** Load the keymap */
	static UBaseSaveGame* LoadSaveGame();
	
	/** Save the game settings */
	static bool SaveGame(UBaseSaveGame* SaveGame);

private:
	TArray<FEnhancedActionKeyMapping> CurrentKeyMappings;
	TWeakObjectPtr<UPlayerMappableInputConfig> CurrentPlayerMappableConfig;
	TWeakObjectPtr<UPlayerMappableInputConfig> DefaultPlayerMappableInputConfig;
};
