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
	APlayGameMode();

	virtual void BeginPlay() override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

private:
	void SetupSubsystems();
	void SetupDoorInteractionEvents();
	void SetupItemInteractionEvents();

private:
	/** The level coordinator class to use for the main level */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Subsystems", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ALevelCoordinator> LevelCoordinatorClass;

private:
	FSubsystemCache SubsystemCache;
	TWeakObjectPtr<ALevelCoordinator> LevelCoordinator;
};
