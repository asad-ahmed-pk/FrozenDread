//
// MusicData.h
// Definition of the UMusicPlayerSubsystem class.
//

#pragma once

#include "MusicData.generated.h"

class USoundBase;

/**
 * Represents a music track that can be played.
 */
UCLASS(BlueprintType)
class UMusicTrackDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Get access to the sound track for this asset */
	FORCEINLINE USoundBase* GetTrack() const { return MusicTrack; }

private:
	/** The name of the music track */
	UPROPERTY(EditAnywhere, Category="Data", meta=(AllowPrivateAccess="true"))
	FName TrackName;

	/** The music file for the track */
	UPROPERTY(EditAnywhere, Category="Data", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundBase> MusicTrack;
};
