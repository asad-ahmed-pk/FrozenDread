//
// CreditsWidget.cpp
// Implementation of the UCreditsWidget class.
//


#include "CreditsWidget.h"

#include "Components/Button.h"


void UCreditsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UCreditsWidget::BackButtonClicked);
	}
}

void UCreditsWidget::BackButtonClicked()
{
	OnBackButtonClicked.Broadcast();
}
