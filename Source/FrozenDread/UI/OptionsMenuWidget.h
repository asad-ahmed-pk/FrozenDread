//
// OptionsMenuWidget.h
// Definition of the UOptionsMenuWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FrozenDread/Game/MainUserInterface.h"
#include "OptionsMenuWidget.generated.h"

class UButton;

DECLARE_MULTICAST_DELEGATE(FKeyBindsOptionClicked);
DECLARE_MULTICAST_DELEGATE(FSettingsButtonClicked);

/**
 * Widget for displaying the top level game options for the user to customise.
 */
UCLASS()
class FROZENDREAD_API UOptionsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private:
	UFUNCTION()
	void KeyBindsButtonClicked();

	UFUNCTION()
	void BackButtonClicked();

	UFUNCTION()
	void SettingsButtonClicked();
	
public:
	FKeyBindsOptionClicked OnKeyBindButtonClicked;
	FSettingsButtonClicked OnSettingsButtonClicked;
	FBackButtonClickDelegate OnBackButtonClicked;

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> KeyBindsButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> SettingsButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> BackButton;
};
