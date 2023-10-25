//
// BaseGameInstance.h
// Definition of the UBaseGameInstance class.
//


#pragma once

#include "CoreMinimal.h"
#include "MainUserInterface.h"
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

	/** Player requests game options to be displayed */
	void OptionsMenuRequested() const;

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

	/** The set of widget classes to use for the game (excludes in-game UI such as inventory) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	FGameWidgetClass WidgetBlueprintClasses;

private:
	TWeakObjectPtr<UGameUISubsystem> GameUISubsystem;
	TObjectPtr<UUserWidget> LoadingScreenWidget;
};
