//
// PauseMenu.h
// Definition of the UPauseMenu class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class UButton;

/**
 * The in-game menu to show when the player pauses the game.
 */
UCLASS()
class FROZENDREAD_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OptionsButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();

	UFUNCTION()
	void ResumeButtonClicked();

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> ResumeButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> ExitToMenuButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> OptionsButton;
};
