//
// GameUISubsystem.h
// Definition of the UGameUISubsystem class.
//

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameUISubsystem.generated.h"

/**
 * Subsystem responsible for the main game UI (main menu, options screen, etc...) and NOT the in-game player UI (HUD).
 */
UCLASS()
class FROZENDREAD_API UGameUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Init this subsystem */
	void Init(UUserWidget* LoadingWidget);

	/** Show the loading screen and call the callback */
	void ShowLoadingScreen(const TFunction<void()>& CompletionCallBack);

	/** Hide the loading screen */
	void HideLoadingScreen();

private:
	void OnMapPostLoad(UWorld* World);

private:
	bool IsLoadingScreenActive { false };
	FTimerHandle TimerHandle;
	TWeakObjectPtr<UUserWidget> LoadingScreenWidget;
};
