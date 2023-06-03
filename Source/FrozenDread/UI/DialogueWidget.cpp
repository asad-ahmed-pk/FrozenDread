//
// DialogueWidget.cpp
// Implementation of the UDialogueWidget class.
//

#include "FrozenDread/UI/DialogueWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

void UDialogueWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	bIsFocusable = true;
}

void UDialogueWidget::SetText(const FString& Text)
{
	check(DialogueTextBlock);
	IsWaitingForInput = false;
	DialogueTextBlock->SetText(FText::FromString(Text));
}

void UDialogueWidget::SetToNextMode()
{
	check(NextIcon);
	NextIcon->SetVisibility(ESlateVisibility::Visible);
	IsWaitingForInput = true;
}

FReply UDialogueWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (IsWaitingForInput)
	{
		NextEvent.Broadcast();
	}

	return FReply::Handled();
}

FReply UDialogueWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (IsWaitingForInput)
	{
		NextEvent.Broadcast();
	}

	return FReply::Handled();
}
