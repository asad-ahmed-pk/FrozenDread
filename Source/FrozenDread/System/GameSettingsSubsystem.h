//
// GameSettingsSubsystem.h
// Definition of the UGameInstanceSubsystem class.
//

#pragma once

#include "CoreMinimal.h"
#include "EnhancedActionKeyMapping.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "FrozenDread/Game/GameOptions.h"

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
	void UpdateKeyMappings(const TArray<FEnhancedActionKeyMapping>& Mappings);

	/** Get the current saved graphics options for the game */
	static GameSettings::FGraphicsOptions GetGraphicsOptions();

	/** Apply and save the graphics options for the game with the following settings */
	static void ApplyGraphicsOptions(const GameSettings::FGraphicsOptions& GraphicsOptions);

private:
	static UBaseSaveGame* LoadSaveGame();
	static bool SaveGame(UBaseSaveGame* SaveGame);
	void SyncKeyMappings(const TArray<FEnhancedActionKeyMapping>& NewMappings) const;

private:
	TArray<FEnhancedActionKeyMapping> CurrentKeyMappings;
	TWeakObjectPtr<UPlayerMappableInputConfig> CurrentPlayerMappableConfig;
	TWeakObjectPtr<UPlayerMappableInputConfig> DefaultPlayerMappableInputConfig;
};
