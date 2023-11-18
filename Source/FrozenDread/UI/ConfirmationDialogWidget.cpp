//
// ConfirmationDialogWidget.cpp
// Implementation of the UConfirmationDialogWidget class.
//

#include "ConfirmationDialogWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UConfirmationDialogWidget::SetContent(const FText& Title, const FText& Message) const
{
	TitleText->SetText(Title);
	MessageText->SetText(Message);
}

void UConfirmationDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (YesButton)
	{
		YesButton->OnClicked.AddDynamic(this, &UConfirmationDialogWidget::OnYesButtonClicked);
	}

	if (NoButton)
	{
		NoButton->OnClicked.AddDynamic(this, &UConfirmationDialogWidget::OnNoButtonClicked);
	}
}

void UConfirmationDialogWidget::OnYesButtonClicked()
{
	OnConfirmationResultSelected.Execute(true);
}

void UConfirmationDialogWidget::OnNoButtonClicked()
{
	OnConfirmationResultSelected.Execute(false);
}
