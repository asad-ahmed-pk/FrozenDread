//
// BaseGameInstance.h
// Definition of the UBaseGameInstance class.
//


#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

class UGameUISubsystem;
class UPlayerMappableInputConfig;
class UMusicTrackDataAsset;

/**
 * Default game instance for this game.
 */
UCLASS()
class FROZENDREAD_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/** Player requested to start the game */
	void StartGameRequested() const;
	
	/** Player requested to quit the game */
	static void QuitGameRequested();

protected:
	virtual void OnStart() override;

private:
	void SetupSubsystems() const;
	void SetupGameUI();
		

private:
	/** The list of music tracks for this game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Music", meta=(AllowPrivateAccess="true"))
	TArray<UMusicTrackDataAsset*> MusicTrackList;

	/** The default mappable player input config for the game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UPlayerMappableInputConfig> PlayerMappableInputConfig;

	/** The loading screen widget class to use for the loading screen */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUserWidget> LoadingScreenWidgetClass;

private:
	TWeakObjectPtr<UGameUISubsystem> GameUISubsystem;
	TObjectPtr<UUserWidget> LoadingScreenWidget;
};
