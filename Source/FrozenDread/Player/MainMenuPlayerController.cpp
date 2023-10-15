//
// MainMenuPlayerController.cpp
// Implementation of the AMainMenuPlayerController class.
//


#include "MainMenuPlayerController.h"

#include "Blueprint/UserWidget.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);

	// Show the main menu UI
	check(MainMenuWidgetClass);
	MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	MainMenuWidget->AddToViewport();
}
