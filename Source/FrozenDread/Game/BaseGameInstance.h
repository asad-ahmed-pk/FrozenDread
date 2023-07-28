//
// BaseGameInstance.h
// Definition of the UBaseGameInstance class.
//


#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

class UMusicTrackDataAsset;

/**
 * Default game instance for this game.
 */
UCLASS()
class FROZENDREAD_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void OnStart() override;

private:
	/** The list of music tracks for this game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Music", meta=(AllowPrivateAccess="true"))
	TArray<UMusicTrackDataAsset*> MusicTrackList;
};
