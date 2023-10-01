//
// MusicData.h
// Definition of the UMusicPlayerSubsystem class.
//

#pragma once

#include "MusicData.generated.h"

class USoundBase;

/** The type of music track */
UENUM(BlueprintType)
enum class EMusicTrackType : uint8
{
	MainMenu				UMETA(DisplayName="Main Menu"),
	Gameplay				UMETA(DisplayName="Regular Gameplay"),
	MonsterChase			UMETA(DisplayName="Monster Chase")
};

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

	/** Get the name of the track for this asset */
	FORCEINLINE FName GetTrackName() const { return TrackName; }

	/** Get the type of this track asset */
	FORCEINLINE EMusicTrackType GetTrackType() const { return Type; }

private:
	/** The name of the music track */
	UPROPERTY(EditAnywhere, Category="Data", meta=(AllowPrivateAccess="true"))
	FName TrackName;

	/** The music file for the track */
	UPROPERTY(EditAnywhere, Category="Data", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundBase> MusicTrack;

	/** The type of music track */
	UPROPERTY(EditAnywhere, Category="Data", meta=(AllowPrivateAccess="true"))
	EMusicTrackType Type;
};
