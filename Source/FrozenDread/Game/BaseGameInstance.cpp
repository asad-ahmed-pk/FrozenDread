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
#include "Misc/MessageDialog.h"


void UBaseGameInstance::OnStart()
{
	Super::OnStart();
	SetupSubsystems();
	SetupGameUI();
}

void UBaseGameInstance::SetupSubsystems() const
{
	// Setup music subsystem
	UMusicPlayerSubsystem* MusicPlayerSubsystem { GetSubsystem<UMusicPlayerSubsystem>() };
	check(MusicPlayerSubsystem);
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

void UBaseGameInstance::QuitGameRequested()
{
	const FText Message { FText::FromString("Are you sure you want to quit") };
	const FText Title { FText::FromString("Quit Game") };
	const EAppReturnType::Type ReturnType { FMessageDialog::Open(EAppMsgType::YesNo, Message, &Title) };

	if (ReturnType == EAppReturnType::Yes)
	{
		FGenericPlatformMisc::RequestExit(false);
	}
}
