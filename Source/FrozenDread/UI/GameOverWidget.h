//
// GameOverWidget.h
// Definition of the UGameOverWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

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
	/** Display the widget and play the game over animation */
	void Show();

protected:
	/** The main canvas for the widget */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UCanvasPanel> MainCanvasPanel;

	/** The main animation to play */
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> Animation;
};
