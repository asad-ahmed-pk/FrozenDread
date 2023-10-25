//
// KeyBindsWidget.h
// Definition of the UKeyBindsWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "EnhancedActionKeyMapping.h"
#include "Blueprint/UserWidget.h"
#include "FrozenDread/Game/MainUserInterface.h"

#include "KeyBindsWidget.generated.h"

class UButton;
class UScrollBox;
class UGameUISubsystem;
class UTextBlock;

/**
 * Widget for customising the player's key binds.
 */
UCLASS()
class FROZENDREAD_API UKeyBindsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private:
	UFUNCTION()
	void Close();

private:
	void SetupKeyBindsScrollBox();
	void SetIsInKeyBindModeForIndex(int32 KeyBindIndex);
	void SetIsNotInKeyBindMode();
	void OnKeyBindWidgetOptionClicked(UUserWidget* OptionWidget);

public:
	FBackButtonClickDelegate OnCloseButtonClicked;

protected:
	/** The scroll view that will contain the keybind widgets */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UScrollBox> KeyBindsScrollView;

	/** The text that will display the current status (eg; bind button to) */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> StatusText;

	/** The close button to dismiss this widget */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> CloseButton;

	/** The animation to play when a key bind is in progress */
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* BindInProgressAnimation;

	/** The widget class to use for the key bind widgets in the scroll view */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> KeyBindOptionWidgetClass;

private:
	int32 SelectedKeyMappingIndex { -1 };
	TMap<UUserWidget*, int32> KeyBindWidgetIndexes;
	TArray<FEnhancedActionKeyMapping> KeyMappings;
	TWeakObjectPtr<UGameUISubsystem> GameUISubsystem;
};
