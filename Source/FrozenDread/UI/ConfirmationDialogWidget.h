//
// ConfirmationDialogWidget.h
// Definition of the UConfirmationDialogWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmationDialogWidget.generated.h"

class UButton;
class UTextBlock;

DECLARE_DELEGATE_OneParam(FDialogWidgetResult, bool);

/**
 * Dialog widget that displays a message and asks for confirmation from the user.
 */
UCLASS()
class FROZENDREAD_API UConfirmationDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Set the title and message text on this dialog */
	void SetContent(const FText& Title, const FText& Message) const;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnYesButtonClicked();

	UFUNCTION()
	void OnNoButtonClicked();

public:
	FDialogWidgetResult OnConfirmationResultSelected;

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> TitleText;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> MessageText;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> YesButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> NoButton;
};
