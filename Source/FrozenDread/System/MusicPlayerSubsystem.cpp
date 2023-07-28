//
// MusicPlayerSubsystem.cpp
// Implementation of the UMusicPlayerSubsystem class.
//

#include "MusicPlayerSubsystem.h"

#include "Components/AudioComponent.h"
#include "FrozenDread/Game/MusicData.h"
#include "Kismet/GameplayStatics.h"

void UMusicPlayerSubsystem::SetupWithTrackList(const TArray<UMusicTrackDataAsset*>& TrackList)
{
	MusicTrackList = &TrackList;
	if (AudioPlayer == nullptr)
	{
		AudioPlayer = UGameplayStatics::SpawnSound2D(this, nullptr);
	}
}

void UMusicPlayerSubsystem::PlayTrack(int32 TrackIndex)
{
	// Get the given track
	check(MusicTrackList);
	const UMusicTrackDataAsset* Asset { (*MusicTrackList)[TrackIndex] };
	USoundBase* Track { Asset->GetTrack() };

	// Create Audio Player
	if (AudioPlayer == nullptr)
	{
		AudioPlayer = UGameplayStatics::SpawnSound2D(
			this,
			Track,
			1,
			1,
			0,
			nullptr,
			false,
			false
		);
		return;
	}

	// Stop previous sound and play this one
	check(AudioPlayer);
	if(AudioPlayer->IsPlaying() && CurrentTrack != TrackIndex)
	{
		AudioPlayer->Stop();
	}

	AudioPlayer->SetSound(Track);
	AudioPlayer->Play();
	
	CurrentTrack = TrackIndex;
}

void UMusicPlayerSubsystem::Stop()
{
	check(AudioPlayer);
	if (AudioPlayer->IsPlaying())
	{
		AudioPlayer->Stop();
	}
}
