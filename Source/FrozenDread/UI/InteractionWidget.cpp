//
// InteractionWidget.cpp
// Implementation of the UInteractionWidget class.
//


#include "FrozenDread/UI/InteractionWidget.h"

#include "Components/TextBlock.h"


void UInteractionWidget::SetInteractionText(const FText& Text) const
{
	InteractionText->SetText(Text);
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (InteractionText)
	{
		InteractionText->SetText(FText::FromString(TEXT("Object Name")));
	}
}
