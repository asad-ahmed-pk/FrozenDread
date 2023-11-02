//
// GameSettingsWidget.h
// Definition of the UGameSettingsWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FrozenDread/Game/GameOptions.h"
#include "FrozenDread/Game/MainUserInterface.h"
#include "GameSettingsWidget.generated.h"

class UButton;
class UComboBoxString;
class UCheckBox;

/**
 * Widget for allowing the user to customise the game settings
 */
UCLASS()
class FROZENDREAD_API UGameSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void BackButtonClicked();

	UFUNCTION()
	void SaveButtonClicked();

	UFUNCTION()
	void ComboBoxSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void CheckBoxSelectionChanged(bool NewState);

private:
	void SyncUIWithSettings();
	GameSettings::FGraphicsOptions ExtractOptionsFromUI();

public:
	FBackButtonClickDelegate OnBackButtonClicked;

protected:
	/** The close button */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> CloseButton;

	/** Save settings button */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> SaveButton;
	
	/** The check box to toggle Lumen on and off */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UCheckBox> EnableLumenCheckBox;

	/** The drop down to select the overall graphics quality */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UComboBoxString> GraphicsQualityComboBox;

	/** The drop down to select the screen resolution */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UComboBoxString> ScreenResolutionComboBox;
};
