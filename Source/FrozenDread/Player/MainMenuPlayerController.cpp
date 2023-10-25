//
// MainMenuPlayerController.cpp
// Implementation of the AMainMenuPlayerController class.
//


#include "MainMenuPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "FrozenDread/Game/GameStatics.h"
#include "FrozenDread/System/MusicPlayerSubsystem.h"

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

	// Play main menu music
	UGameStatics::GetMusicSubsystem(this)->PlayRandomTrack(EMusicTrackType::MainMenu);
}
