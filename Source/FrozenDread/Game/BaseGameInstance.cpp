// Fill out your copyright notice in the Description page of Project Settings.


#include "FrozenDread/Game/BaseGameInstance.h"

#include "FrozenDread/System/GameSettingsSubsystem.h"
#include "FrozenDread/System/MusicPlayerSubsystem.h"

void UBaseGameInstance::OnStart()
{
	Super::OnStart();

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
