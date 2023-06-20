//
// GameOverWidget.h
// Definition of the UGameOverWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UButton;
class UCanvasPanel;
class UWidgetAnimation;

/**
 * Widget for presenting the game over screen.
 */
UCLASS()
class FROZENDREAD_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Constructor for this widget */
	virtual void NativeConstruct() override;
	
	/** Display the widget and play the game over animation */
	void Show();

private:
	UFUNCTION()
	void QuitButtonClicked();

	UFUNCTION()
	void RestartButtonClicked();

protected:
	/** The main canvas for the widget */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UCanvasPanel> MainCanvasPanel;

	/** The main animation to play */
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> Animation;

	/** The quit button that quits to the main menu */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> QuitButton;

	/** The button to restart the level */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> RestartButton;
};
