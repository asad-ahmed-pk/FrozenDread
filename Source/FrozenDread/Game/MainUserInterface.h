//
// MainUserInterface.h
// Game UI constants and definitions.
//

#pragma once

#include "MainUserInterface.generated.h"

class UUserWidget;

DECLARE_MULTICAST_DELEGATE(FBackButtonClickDelegate);

USTRUCT(BlueprintType)
struct FGameWidgetClass
{
	GENERATED_BODY()

	/** The loading screen widget to use for the game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> LoadingScreenWidget;
	
	/** The widget to use for the game options menu */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> GameOptionsWidgetClass;

	/** The widget to use for the key binds UI */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> KeyBindsWidgetClass;

	/** The widget to use for the game settings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> GameSettingsWidgetClass;

	/** The widget to use for the game credits screen */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> CreditsWidgetClass;
};
