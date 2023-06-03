//
// DialogueWidget.h
// Definition of the UDialogueWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

class UTextBlock;
class UImage;

/** This event is triggered when the player requests the "Next" action on this dialogue widget */
DECLARE_MULTICAST_DELEGATE(FDialogueWidgetNextEvent);

/**
 * Widget for displaying the player's dialogue text.
 */
UCLASS()
class FROZENDREAD_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	/** Set the display text to show the player */
	void SetText(const FString& Text);

	/** Show the "next" icon and wait for player input to proceed */
	void SetToNextMode();

	/** Get a reference to the next event */
	FDialogueWidgetNextEvent& GetNextEventRef() { return NextEvent; }

protected:
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

protected:
	/** The text block to use for the dialogue */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> DialogueTextBlock;

	/** The icon that shows the "next" symbol */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> NextIcon;

private:
	bool IsWaitingForInput { false };
	FDialogueWidgetNextEvent NextEvent;
};
