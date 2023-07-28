//
// MusicPlayerSubsystem.h
// Definition of the UMusicPlayerSubsystem class.
//

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MusicPlayerSubsystem.generated.h"

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

	/** Play track at the given index */
	UFUNCTION(BlueprintCallable, Category="Music Subsystem")
	void PlayTrack(int32 TrackIndex);

	/** Stop playing music */
	UFUNCTION(BlueprintCallable, Category="Music Subsystem")
	void Stop();

private:
	UPROPERTY()
	TObjectPtr<UAudioComponent> AudioPlayer { nullptr };

private:
	int32 CurrentTrack { -1 };
	const TArray<UMusicTrackDataAsset*>* MusicTrackList;
};
