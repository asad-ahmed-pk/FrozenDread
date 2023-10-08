//
// MusicPlayerSubsystem.cpp
// Implementation of the UMusicPlayerSubsystem class.
//

#include "MusicPlayerSubsystem.h"

#include "Algo/Copy.h"
#include "Components/AudioComponent.h"
#include "FrozenDread/Game/MusicData.h"
#include "Kismet/GameplayStatics.h"

void UMusicPlayerSubsystem::SetupWithTrackList(const TArray<UMusicTrackDataAsset*>& TrackList)
{
	MusicTrackList = &TrackList;
}

void UMusicPlayerSubsystem::PlayRandomTrack(EMusicTrackType TrackType)
{
	check(MusicTrackList);

	TArray<UMusicTrackDataAsset*> TrackAssets;
	Algo::CopyIf(*MusicTrackList, TrackAssets, [TrackType](const UMusicTrackDataAsset* Asset)
	{
		return Asset->GetTrackType() == TrackType;
	});

	check(!TrackAssets.IsEmpty());

	const int32 Index { FMath::RandRange(0, TrackAssets.Num() - 1) };
	PlayTrack(TrackAssets[Index]);
}

void UMusicPlayerSubsystem::OnTrackFinished(UAudioComponent* Component)
{
	// Only switch to a new track if audio completed playing to end and was not stopped manually
	if (AudioWasStopped)
	{
		return;
	}

	check(CurrentlyPlayingAsset.IsValid());

	// Select and play next track based on the current track that stopped playing
	switch (CurrentlyPlayingAsset->GetTrackType())
	{
	case EMusicTrackType::Intro:
	case EMusicTrackType::Gameplay:
		PlayRandomTrack(EMusicTrackType::Gameplay);
		break;

	case EMusicTrackType::MainMenu:
		PlayRandomTrack(EMusicTrackType::MainMenu);
		break;

	case EMusicTrackType::MonsterChase:
		PlayRandomTrack(EMusicTrackType::MonsterChase);
		break;
	}
}

void UMusicPlayerSubsystem::PlayTrack(const UMusicTrackDataAsset* TrackAsset)
{
	if (AudioPlayer == nullptr)
	{
		// Lazy init audio component
		AudioPlayer = UGameplayStatics::SpawnSound2D(this, TrackAsset->GetTrack(), 1, 1, 0, nullptr, true, false);
		AudioPlayer->OnAudioFinishedNative.AddUObject(this, &UMusicPlayerSubsystem::OnTrackFinished);
	}
	else
	{
		// Stop current track and switch to new track
		if (CurrentlyPlayingAsset != TrackAsset)
		{
			StopCurrentTrack();
			
			AudioPlayer->SetSound(TrackAsset->GetTrack());
			AudioPlayer->Play();

			AudioWasStopped = false;
		}
	}

	CurrentlyPlayingAsset = TrackAsset;
}

void UMusicPlayerSubsystem::StopCurrentTrack()
{
	check(AudioPlayer);
	if (AudioPlayer->IsPlaying())
	{
		AudioPlayer->Stop();
		AudioWasStopped = true;
	}

	CurrentlyPlayingAsset = nullptr;
}
