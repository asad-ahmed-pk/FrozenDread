//
// KeyBindOptionWidget.cpp
// Implementation of the UKeyBindOptionWidget class.
//


#include "KeyBindOptionWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "FrozenDread/Game/KeyBindOption.h"

void UKeyBindOptionWidget::SetKeyBindForAction(const FEnhancedActionKeyMapping& Action) const
{
	KeyBindButtonText->SetText(Action.Key.GetDisplayName());
	InputActionNameText->SetText(Action.PlayerMappableOptions.DisplayName);
}

void UKeyBindOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (KeyBindButton)
	{
		KeyBindButton->OnClicked.AddDynamic(this, &UKeyBindOptionWidget::KeyBindButtonClicked);
	}
}

void UKeyBindOptionWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	const UKeyBindOption* KeyBindOption { CastChecked<UKeyBindOption>(ListItemObject) };
	KeyBindButtonText->SetText(KeyBindOption->GetKeyMapping().Key.GetDisplayName());
	InputActionNameText->SetText(KeyBindOption->GetKeyMapping().PlayerMappableOptions.DisplayName);
}

void UKeyBindOptionWidget::KeyBindButtonClicked()
{
	OnKeyBindButtonClicked.Broadcast(this);
}
