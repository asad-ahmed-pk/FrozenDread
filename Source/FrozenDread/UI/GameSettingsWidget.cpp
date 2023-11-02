//
// GameSettingsWidget.cpp
// Implementation of the UGameSettingsWidget class.
//


#include "GameSettingsWidget.h"

#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "FrozenDread/Game/GameOptions.h"
#include "FrozenDread/System/GameSettingsSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UGameSettingsWidget::BackButtonClicked);
	}

	if (SaveButton)
	{
		SaveButton->SetIsEnabled(false);
		SaveButton->OnClicked.AddDynamic(this, &UGameSettingsWidget::SaveButtonClicked);
	}

	// Display current game options
	GameSettings::FGraphicsOptions GraphicsOptions { UGameSettingsSubsystem::GetGraphicsOptions() };

	if (EnableLumenCheckBox)
	{
		EnableLumenCheckBox->SetIsChecked(GraphicsOptions.EnableLumen);
		EnableLumenCheckBox->OnCheckStateChanged.AddDynamic(this, &UGameSettingsWidget::CheckBoxSelectionChanged);
	}

	if (GraphicsQualityComboBox)
	{
		GraphicsQualityComboBox->AddOption("Low");
		GraphicsQualityComboBox->AddOption("Medium");
		GraphicsQualityComboBox->AddOption("High");
		GraphicsQualityComboBox->AddOption("Epic");
		GraphicsQualityComboBox->AddOption("Cinematic");

		GraphicsQualityComboBox->SetSelectedIndex(static_cast<int32>(GraphicsOptions.GraphicsQuality));
		GraphicsQualityComboBox->OnSelectionChanged.AddDynamic(this, &UGameSettingsWidget::ComboBoxSelectionChanged);
	}

	if (ScreenResolutionComboBox)
	{
		TArray<FIntPoint> ScreenResolutions;
		UKismetSystemLibrary::GetSupportedFullscreenResolutions(ScreenResolutions);
		for (int32 Index = 0; Index < ScreenResolutions.Num(); Index++)
		{
			const FIntPoint ScreenResolution { ScreenResolutions[Index] };
			ScreenResolutionComboBox->AddOption(FString::Printf(TEXT("%d x %d"), ScreenResolution.X, ScreenResolution.Y));

			if (ScreenResolution == GraphicsOptions.ScreenResolution)
			{
				ScreenResolutionComboBox->SetSelectedIndex(Index);
			}
		}

		ScreenResolutionComboBox->OnSelectionChanged.AddDynamic(this, &UGameSettingsWidget::ComboBoxSelectionChanged);
	}
}

void UGameSettingsWidget::BackButtonClicked()
{
	// Set UI to current settings
	SyncUIWithSettings();
	OnBackButtonClicked.Broadcast();
}

void UGameSettingsWidget::SaveButtonClicked()
{
	const GameSettings::FGraphicsOptions GraphicsOptions { ExtractOptionsFromUI() };
	UGameSettingsSubsystem::ApplyGraphicsOptions(GraphicsOptions);
	SaveButton->SetIsEnabled(false);
}

void UGameSettingsWidget::ComboBoxSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	SaveButton->SetIsEnabled(true);
}

void UGameSettingsWidget::CheckBoxSelectionChanged(bool NewState)
{
	SaveButton->SetIsEnabled(true);
}

void UGameSettingsWidget::SyncUIWithSettings()
{
	const auto [EnableLumen, GraphicsQuality, ScreenResolution] { UGameSettingsSubsystem::GetGraphicsOptions() };
	
	check(EnableLumenCheckBox);
	EnableLumenCheckBox->SetIsChecked(EnableLumen);

	check(GraphicsQualityComboBox);
	GraphicsQualityComboBox->SetSelectedIndex(static_cast<int32>(GraphicsQuality));

	check(ScreenResolutionComboBox);
	TArray<FIntPoint> ScreenResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(ScreenResolutions);

	for (int32 Index = 0; Index < ScreenResolutions.Num(); Index++)
	{
		if (ScreenResolutions[Index] == ScreenResolution)
		{
			ScreenResolutionComboBox->SetSelectedIndex(Index);
			break;
		}
	}
	
	SaveButton->SetIsEnabled(false);
}

GameSettings::FGraphicsOptions UGameSettingsWidget::ExtractOptionsFromUI()
{
	GameSettings::FGraphicsOptions GraphicsOptions;
	
	// Lumen setting
	check(EnableLumenCheckBox);
	GraphicsOptions.EnableLumen = EnableLumenCheckBox->IsChecked();

	// Graphics Quality
	check(GraphicsQualityComboBox);
	GraphicsOptions.GraphicsQuality = static_cast<GameSettings::EScale>(GraphicsQualityComboBox->GetSelectedIndex());

	if (!GraphicsOptions.EnableLumen)
	{
		// If lumen is not enabled graphics must be <= MEDIUM
		if (static_cast<int32>(GraphicsOptions.GraphicsQuality) > static_cast<int32>(GameSettings::EScale::SCALE_MEDIUM))
		{
			GraphicsOptions.GraphicsQuality = GameSettings::EScale::SCALE_MEDIUM;
		}
	}
	else
	{
		// If lumen is enabled graphics must be >= EPIC
		if (static_cast<int32>(GraphicsOptions.GraphicsQuality) < static_cast<int32>(GameSettings::EScale::SCALE_EPIC))
		{
			GraphicsOptions.GraphicsQuality = GameSettings::EScale::SCALE_EPIC;
		}
	}

	// Screen Resolution
	check(ScreenResolutionComboBox)
	TArray<FIntPoint> ScreenResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(ScreenResolutions);
	GraphicsOptions.ScreenResolution = ScreenResolutions[ScreenResolutionComboBox->GetSelectedIndex()];

	return GraphicsOptions;
}
