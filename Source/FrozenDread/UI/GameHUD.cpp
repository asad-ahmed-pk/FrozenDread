//
// GameHUD.cpp
// Implementation of the AGameHUD class.
//

#include "FrozenDread/UI/GameHUD.h"

#include "CinematicWidget.h"
#include "GameOverWidget.h"
#include "ObjectiveWidget.h"
#include "PauseMenuWidget.h"
#include "FrozenDread/UI/InteractionWidget.h"
#include "FrozenDread/UI/InventoryWidget.h"
#include "FrozenDread/UI/DialogueWidget.h"
#include "FrozenDread/Player/GamePlayerController.h"

void AGameHUD::InitAndAddToViewport()
{
	check(InteractionWidgetClass);

	AGamePlayerController* PlayerController { Cast<AGamePlayerController>(GetOwner()) };

	// Cinematic Widget
	check(CinematicWidgetClass);
	CinematicWidget = CreateWidget<UCinematicWidget>(PlayerController, CinematicWidgetClass);
	CinematicWidget->AddToViewport(-1);
	CinematicWidget->SetVisibility(ESlateVisibility::Collapsed);

	// Objectives Widget
	check(ObjectiveWidgetClass);
	ObjectiveWidget = CreateWidget<UObjectiveWidget>(PlayerController, ObjectiveWidgetClass);
	ObjectiveWidget->AddToViewport(0);
	ObjectiveWidget->SetVisibility(ESlateVisibility::Visible);

	// Interaction Widget
	check(InteractionWidgetClass);
	InteractionWidget = CreateWidget<UUserWidget>(PlayerController, InteractionWidgetClass);
	InteractionWidget->AddToViewport(1);

	// Inventory Widget
	check(InventoryWidgetClass);
	InventoryWidget = CreateWidget<UUserWidget>(PlayerController, InventoryWidgetClass);
	InventoryWidget->AddToViewport(2);
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

	// Dialogue Widget
	check(DialogueWidgetClass);
	DialogueWidget = CreateWidget<UUserWidget>(PlayerController, DialogueWidgetClass);
	DialogueWidget->AddToViewport(3);
	DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);

	// Pause Menu Widget
	check(PauseMenuWidgetClass);
	PauseMenuWidget = CreateWidget<UUserWidget>(PlayerController, PauseMenuWidgetClass);
	PauseMenuWidget->AddToViewport(4);
	PauseMenuWidget->SetVisibility(ESlateVisibility::Collapsed);

	// Game Over Widget
	check(GameOverWidgetClass);
	GameOverWidget = CreateWidget<UUserWidget>(PlayerController, GameOverWidgetClass);
	GameOverWidget->AddToViewport(5);
	GameOverWidget->SetVisibility(ESlateVisibility::Collapsed);
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

UGameOverWidget* AGameHUD::GetGameOverWidget() const
{
	check(GameOverWidget);
	return Cast<UGameOverWidget>(GameOverWidget);
}

UPauseMenuWidget* AGameHUD::GetPauseMenuWidget() const
{
	check(PauseMenuWidget);
	return Cast<UPauseMenuWidget>(PauseMenuWidget);
}

UObjectiveWidget* AGameHUD::GetObjectiveWidget() const
{
	check(ObjectiveWidget);
	return Cast<UObjectiveWidget>(ObjectiveWidget);
}

UCinematicWidget* AGameHUD::GetCinematicWidget() const
{
	check(CinematicWidget);
	return Cast<UCinematicWidget>(CinematicWidget);
}
