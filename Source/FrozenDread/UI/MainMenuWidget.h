//
// MainMenuWidget.cpp
// Definition of the UMainMenuWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
/**
 * Widget for the game's main menu.
 */
UCLASS()
class FROZENDREAD_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	/** The button to start the game */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> StartGameButton;

	/** The button to end the game */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> EndGameButton;

	/** The button to show the options sub menu */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> OptionsButton;

private:
	UFUNCTION()
	void StartGameButtonPressed();

	UFUNCTION()
	void EndGameButtonPressed();
};
