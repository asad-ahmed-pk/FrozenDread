//
// BaseGameInstance.cpp
// Implementation of the UBaseGameInstance class.
//


#include "FrozenDread/Game/BaseGameInstance.h"

#include "FrozenDread/Level/LevelObjects.h"
#include "FrozenDread/System/GameSettingsSubsystem.h"
#include "FrozenDread/System/GameUISubsystem.h"
#include "FrozenDread/System/MusicPlayerSubsystem.h"
#include "Kismet/GameplayStatics.h"


void UBaseGameInstance::StartGameInstance()
{
	SetupSubsystems();
	SetupGameUI();
	Super::StartGameInstance();
}

void UBaseGameInstance::SetupSubsystems() const
{
	// Setup music subsystem
	UMusicPlayerSubsystem* MusicPlayerSubsystem { GetSubsystem<UMusicPlayerSubsystem>() };
	check(MusicPlayerSubsystem);
	check(!MusicTrackList.IsEmpty());
	MusicPlayerSubsystem->SetupWithTrackList(MusicTrackList);

	// Setup settings subsystem
	UGameSettingsSubsystem* SettingsSubsystem { GetSubsystem<UGameSettingsSubsystem>() };
	check(SettingsSubsystem);
	check(PlayerMappableInputConfig);
	SettingsSubsystem->Init(PlayerMappableInputConfig);
}

void UBaseGameInstance::SetupGameUI()
{
	// Setup Game UI Subsystem
	GameUISubsystem =  GetSubsystem<UGameUISubsystem>();
	check(GameUISubsystem.IsValid());
	GameUISubsystem->Init(WidgetBlueprintClasses);
}

void UBaseGameInstance::StartGameRequested() const
{
	// Show loading screen
	check(GameUISubsystem.IsValid());
	auto CallBack = [&]{
		UGameplayStatics::OpenLevel(this, LevelNames::GAME);
	};
	GameUISubsystem->ShowLoadingScreen(CallBack);
}

void UBaseGameInstance::QuitGameRequested() const
{
	check(GameUISubsystem.IsValid());
	
	const FText Title { FText::FromString("Quit Game") };
	const FText Message { FText::FromString("Are you sure you want to quit") };

	GameUISubsystem->ShowConfirmationDialog(EConfirmationDialogType::QUIT_GAME, [](bool IsConfirmed)
	{
		if (IsConfirmed)
		{
			FGenericPlatformMisc::RequestExit(false);
		}
	});
}

void UBaseGameInstance::ReturnToMainMenuRequested()
{
	check(GameUISubsystem.IsValid());
	auto CallBack = [this] {
		UGameplayStatics::OpenLevel(this, LevelNames::MAIN_MENU);
	};
	GameUISubsystem->ShowLoadingScreen(CallBack);
}

void UBaseGameInstance::OnStart()
{
	Super::OnStart();
	
#if UE_EDITOR
	SetupSubsystems();
	SetupGameUI();
#endif
}
