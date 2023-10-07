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
	PlayTrackAsset(TrackAssets[Index]);
}

void UMusicPlayerSubsystem::PlayTrackAsset(const UMusicTrackDataAsset* TrackAsset)
{
	// Lazy init audio component
	if (AudioPlayer == nullptr)
	{
		CurrentTrackName = TrackAsset->GetTrackName();
		AudioPlayer = UGameplayStatics::SpawnSound2D(this, TrackAsset->GetTrack(), 1, 1, 0, nullptr, true, false);
		return;
	}
	
	// Stop previous sound and play this one
	check(AudioPlayer);
	if(AudioPlayer->IsPlaying() && CurrentTrackName != TrackAsset->GetTrackName())
	{
		AudioPlayer->Stop();
	}

	// Play this track
	AudioPlayer->SetSound(TrackAsset->GetTrack());
	AudioPlayer->Play();

	CurrentTrackName = TrackAsset->GetTrackName();
}

void UMusicPlayerSubsystem::Stop() const
{
	check(AudioPlayer);
	if (AudioPlayer->IsPlaying())
	{
		AudioPlayer->Stop();
	}
}
