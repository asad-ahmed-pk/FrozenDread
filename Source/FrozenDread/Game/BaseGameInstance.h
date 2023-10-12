//
// BaseGameInstance.h
// Definition of the UBaseGameInstance class.
//


#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

class UPlayerMappableInputConfig;
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

	/** The default mappable player input config for the game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UPlayerMappableInputConfig> PlayerMappableInputConfig;
};
