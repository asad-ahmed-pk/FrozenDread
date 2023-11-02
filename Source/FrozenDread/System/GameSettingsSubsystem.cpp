﻿//
// GameSettingsSubsystem.cpp
// Implementation of the UGameInstanceSubsystem class.
//

#include "FrozenDread/System/GameSettingsSubsystem.h"
#include "FrozenDread/Game/BaseSaveGame.h"

#include "PlayerMappableInputConfig.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

constexpr char* SAVE_SLOT_NAME { "DefaultSaveSlot" };

void UGameSettingsSubsystem::Init(UPlayerMappableInputConfig* PMIC)
{
	// Set references
	DefaultPlayerMappableInputConfig = PMIC;

	// Load the keybinds from the save game
	if (const UBaseSaveGame* SaveGame { LoadSaveGame() })
	{
		CurrentKeyMappings = SaveGame->KeyMappings;
	}
}

UBaseSaveGame* UGameSettingsSubsystem::LoadSaveGame()
{
	if (UBaseSaveGame* SaveGame = Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(SAVE_SLOT_NAME, 0)))
	{
		return SaveGame;
	}

	return nullptr;
}

bool UGameSettingsSubsystem::SaveGame(UBaseSaveGame* SaveGame)
{
	check(SaveGame);
	return (UGameplayStatics::SaveGameToSlot(SaveGame, SAVE_SLOT_NAME, 0));
}

void UGameSettingsSubsystem::GetKeyMappings(TArray<FEnhancedActionKeyMapping>& Mappings) const
{
	if (CurrentKeyMappings.Num() > 0)
	{
		Mappings = CurrentKeyMappings;
	}
	else
	{
		check(DefaultPlayerMappableInputConfig.IsValid());
		Mappings = DefaultPlayerMappableInputConfig->GetPlayerMappableKeys();
	}
}

void UGameSettingsSubsystem::UpdateKeyMappings(const TArray<FEnhancedActionKeyMapping>& Mappings)
{
	// Load a save otherwise create a new save if there is no save
	UBaseSaveGame* BaseSaveGame { LoadSaveGame() };
	if (BaseSaveGame == nullptr)
	{
		USaveGame* NewSave { UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()) };
		BaseSaveGame = CastChecked<UBaseSaveGame>(NewSave);
	}

	// Update key mappings and save back
	check(BaseSaveGame);
	BaseSaveGame->KeyMappings = Mappings;
	SaveGame(BaseSaveGame);
}

GameSettings::FGraphicsOptions UGameSettingsSubsystem::GetGraphicsOptions()
{
	// Get the game settings from disk
	UGameUserSettings* GameUserSettings { UGameUserSettings::GetGameUserSettings() };
	GameUserSettings->LoadSettings();

	// Create simple graphic options
	GameSettings::FGraphicsOptions Options;

	// Lumen
	Options.EnableLumen = GameUserSettings->GetGlobalIlluminationQuality() > static_cast<int32>(GameSettings::EScale::SCALE_MEDIUM);

	// Overall graphics quality
	Options.GraphicsQuality = static_cast<GameSettings::EScale>(GameUserSettings->GetOverallScalabilityLevel());

	// Screen Resolution
	Options.ScreenResolution = GameUserSettings->GetScreenResolution();

	return Options;
}

void UGameSettingsSubsystem::ApplyGraphicsOptions(const GameSettings::FGraphicsOptions& GraphicsOptions)
{
	// Get the game settings from disk
	UGameUserSettings* GameUserSettings { UGameUserSettings::GetGameUserSettings() };
	GameUserSettings->LoadSettings();

	// Overall graphics quality
	GameUserSettings->SetOverallScalabilityLevel(static_cast<int32>(GraphicsOptions.GraphicsQuality));

	// Lumen
	GameSettings::EScale LightingScale { GraphicsOptions.EnableLumen ? GameSettings::EScale::SCALE_EPIC : GameSettings::EScale::SCALE_MEDIUM };
	GameUserSettings->SetGlobalIlluminationQuality(static_cast<int32>(LightingScale));

	// Screen resolution
	GameUserSettings->SetScreenResolution(GraphicsOptions.ScreenResolution);

	// Save to disk
	GameUserSettings->ApplySettings(false);
}
