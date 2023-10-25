//
// KeyBindsWidget.cpp
// Implementation of the UKeyBindsWidget class.
//

#include "KeyBindsWidget.h"

#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

#include "FrozenDread/UI/KeyBindOptionWidget.h"
#include "FrozenDread/System/GameSettingsSubsystem.h"
#include "FrozenDread/System/GameUISubsystem.h"

void UKeyBindsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Cache the game UI subsystem
	GameUISubsystem = GetGameInstance()->GetSubsystem<UGameUISubsystem>();

	if (StatusText)
	{
		StatusText->SetText(FText::FromString(""));
	}

	// Initial setup for the key binds scroll view
	if (KeyBindsScrollView)
	{
		SetupKeyBindsScrollBox();
	}

	// Close button
	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UKeyBindsWidget::Close);
	}
}

FReply UKeyBindsWidget::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (SelectedKeyMappingIndex >= 0)
	{
		const FKey Key { InKeyEvent.GetKey() };
		if (Key != EKeys::Escape)
		{
			KeyMappings[SelectedKeyMappingIndex].Key = Key;

			// Update the corresponding option widget
			const UKeyBindOptionWidget* OptionWidget { CastChecked<UKeyBindOptionWidget>(KeyBindsScrollView->GetChildAt(SelectedKeyMappingIndex)) };
			OptionWidget->SetKeyBindForAction(KeyMappings[SelectedKeyMappingIndex]);

			// Set back to normal mode
			SetIsNotInKeyBindMode();
		}

		return FReply::Handled();
	}
	
	return Super::NativeOnKeyUp(InGeometry, InKeyEvent);
}

void UKeyBindsWidget::Close()
{
	// Save the key mappings
	UGameSettingsSubsystem::UpdateKeyMappings(KeyMappings);
	OnCloseButtonClicked.Broadcast();
}

void UKeyBindsWidget::SetupKeyBindsScrollBox()
{
	check(KeyBindsScrollView);

	// Get key binds set in the game
	const UGameSettingsSubsystem* GameSettingsSubsystem { GetGameInstance()->GetSubsystem<UGameSettingsSubsystem>() };
	check(GameSettingsSubsystem);
	GameSettingsSubsystem->GetKeyMappings(KeyMappings);

	// Add all mappings with widgets to the scroll view
	int32 Index { 0 };
	for (const auto& KeyMapping : KeyMappings)
	{
		// Create the key bind option widget
		check(KeyBindOptionWidgetClass);
		UKeyBindOptionWidget* OptionWidget { CreateWidget<UKeyBindOptionWidget>(KeyBindsScrollView, KeyBindOptionWidgetClass) };
		OptionWidget->SetKeyBindForAction(KeyMapping);
		KeyBindsScrollView->AddChild(OptionWidget);
		
		// Subscribe to widget's events
		OptionWidget->OnKeyBindButtonClicked.AddUObject(this, &UKeyBindsWidget::OnKeyBindWidgetOptionClicked);

		// Cache the entry for the list index
		KeyBindWidgetIndexes.Add(OptionWidget, Index++);
	}
}

void UKeyBindsWidget::SetIsInKeyBindModeForIndex(int32 KeyBindIndex)
{
	SelectedKeyMappingIndex = KeyBindIndex;

	// Update text
	const FTextFormat Format = FTextFormat::FromString(TEXT("Binding Key: {0}"));
	const FText Text = FText::Format(Format, KeyMappings[KeyBindIndex].PlayerMappableOptions.DisplayName);
	StatusText->SetText(Text);

	// Play animation
	check(BindInProgressAnimation);
	PlayAnimation(BindInProgressAnimation, 0, 0);
}

void UKeyBindsWidget::SetIsNotInKeyBindMode()
{
	SelectedKeyMappingIndex = -1;
	StatusText->SetText(FText::FromString(""));
	check(BindInProgressAnimation);
	StopAnimation(BindInProgressAnimation);
}

void UKeyBindsWidget::OnKeyBindWidgetOptionClicked(UUserWidget* OptionWidget)
{
	// Ignore if a current key bind is taking place
	if (SelectedKeyMappingIndex >= 0)
	{
		return;
	}

	// Set to key bind mode for index
	const int32 Index { KeyBindWidgetIndexes[OptionWidget] };
	SetIsInKeyBindModeForIndex(Index);
}
