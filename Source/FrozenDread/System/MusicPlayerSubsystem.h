//
// MusicPlayerSubsystem.h
// Definition of the UMusicPlayerSubsystem class.
//

#pragma once

#include "CoreMinimal.h"
#include "FrozenDread/Game/MusicData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MusicPlayerSubsystem.generated.h"

enum class EMusicTrackType : uint8;
class UMusicTrackDataAsset;
class USoundBase;

/**
 * Game instance subsystem that manages background / gameplay music playback.
 */
UCLASS()
class FROZENDREAD_API UMusicPlayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Setup with the track list */
	void SetupWithTrackList(const TArray<UMusicTrackDataAsset*>& TrackList);

	/** Play a random track of the given type */
	void PlayRandomTrack(EMusicTrackType TrackType);

	/** Stop playing music */
	void StopCurrentTrack();

private:
	void OnTrackFinished(UAudioComponent* Component);
	void PlayTrack(const UMusicTrackDataAsset* TrackAsset);

private:
	UPROPERTY()
	TObjectPtr<UAudioComponent> AudioPlayer { nullptr };

private:
	bool AudioWasStopped { false };
	TWeakObjectPtr<const UMusicTrackDataAsset> CurrentlyPlayingAsset;
	const TArray<UMusicTrackDataAsset*>* MusicTrackList;
};


