//
// OptionsMenuWidget.cpp
// Implementation of the UOptionsMenuWidget class.
//


#include "OptionsMenuWidget.h"

#include "Components/Button.h"

void UOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (KeyBindsButton)
	{
		KeyBindsButton->OnClicked.AddDynamic(this, &UOptionsMenuWidget::KeyBindsButtonClicked);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UOptionsMenuWidget::BackButtonClicked);
	}

	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &UOptionsMenuWidget::SettingsButtonClicked);
	}
}

FReply UOptionsMenuWidget::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Escape || InKeyEvent.GetKey() == EKeys::Q)
	{
		OnBackButtonClicked.Broadcast();
	}
	
	return Super::NativeOnKeyUp(InGeometry, InKeyEvent);
}

void UOptionsMenuWidget::KeyBindsButtonClicked()
{
	OnKeyBindButtonClicked.Broadcast();
}

void UOptionsMenuWidget::BackButtonClicked()
{
	OnBackButtonClicked.Broadcast();
}

void UOptionsMenuWidget::SettingsButtonClicked()
{
	OnSettingsButtonClicked.Broadcast();
}
