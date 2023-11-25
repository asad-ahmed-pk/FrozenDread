//
// EndGamePlayerController.cpp
// Implementation of the AEndGamePlayerController class.
//

#include "EndGamePlayerController.h"

#include "Blueprint/UserWidget.h"
#include "FrozenDread/Game/GameStatics.h"
#include "FrozenDread/System/MusicPlayerSubsystem.h"

void AEndGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);

	// Show the end game UI
	check(EndGameWidgetClass);
	EndGameWidget = CreateWidget<UUserWidget>(this, EndGameWidgetClass);
	EndGameWidget->SetVisibility(ESlateVisibility::Visible);
	EndGameWidget->AddToViewport();

	// Play main menu music
	UGameStatics::GetMusicSubsystem(this)->PlayRandomTrack(EMusicTrackType::MainMenu);

	// Notify BP
	WidgetSetupComplete();
}
