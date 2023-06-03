//
// GameHUD.cpp
// Implementation of the AGameHUD class.
//

#include "FrozenDread/UI/GameHUD.h"

#include "FrozenDread/UI/InteractionWidget.h"
#include "FrozenDread/UI/InventoryWidget.h"
#include "FrozenDread/UI/DialogueWidget.h"
#include "FrozenDread/Player/GamePlayerController.h"

void AGameHUD::InitAndAddToViewport()
{
	check(InteractionWidgetClass);

	AGamePlayerController* PlayerController { Cast<AGamePlayerController>(GetOwner()) };

	// Interaction Widget
	check(InteractionWidgetClass);
	InteractionWidget = CreateWidget<UUserWidget>(PlayerController, InteractionWidgetClass);
	InteractionWidget->AddToViewport(0);

	// Inventory Widget
	check(InventoryWidgetClass);
	InventoryWidget = CreateWidget<UUserWidget>(PlayerController, InventoryWidgetClass);
	InventoryWidget->AddToViewport(1);
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

	// Dialogue Widget
	check(DialogueWidgetClass);
	DialogueWidget = CreateWidget<UUserWidget>(PlayerController, DialogueWidgetClass);
	DialogueWidget->AddToViewport(2);
	DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AGameHUD::SetInventoryWidgetVisible(bool IsVisible) const
{
	check(InventoryWidget);
	InventoryWidget->SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

UInteractionWidget* AGameHUD::GetInteractionWidget() const
{
	check(InteractionWidget);
	return Cast<UInteractionWidget>(InteractionWidget);
}

UInventoryWidget* AGameHUD::GetInventoryWidget() const
{
	check(InventoryWidget);
	return Cast<UInventoryWidget>(InventoryWidget);
}

UDialogueWidget* AGameHUD::GetDialogueWidget() const
{
	check(DialogueWidget);
	return Cast<UDialogueWidget>(DialogueWidget);
}
