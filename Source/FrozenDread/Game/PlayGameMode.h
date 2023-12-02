//
// PlayGameMode.h
// Definition of the APlayGameMode class.
//

#pragma once

#include "CoreMinimal.h"
#include "FrozenDread/Level/LevelCoordinator.h"
#include "GameFramework/GameModeBase.h"
#include "PlayGameMode.generated.h"

class AMainLevelCoordinator;
class ALevelCoordinator;
class UGameEventSubsystem;

UCLASS(minimalapi)
class APlayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Called when the game mode is being initialised */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/** Called when the game mode has started */
	virtual void StartPlay() override;

	/** Get a reference to the current level coordinator that is coordinating this level */
	ALevelCoordinator* GetLevelCoordinator() const { return LevelCoordinator.Get(); }

private:
	void SetupSubsystems();
	void SetupDoorInteractionEvents();
	void SetupItemInteractionEvents();
	void SetupTriggerEvents();

private:
	/** The level coordinator class to use for the main level */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Subsystems", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ALevelCoordinator> LevelCoordinatorClass;

private:
	FSubsystemCache SubsystemCache;
	TWeakObjectPtr<ALevelCoordinator> LevelCoordinator;
};
