//
// ObjectiveListItemWidget.cpp
// Implementation of the UObjectiveListItemWidget class.
//

#include "ObjectiveListItemWidget.h"

#include "FrozenDread/Game/Objective.h"

#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UObjectiveListItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (OuterCheckBox)
	{
		OuterCheckBox->SetVisibility(ESlateVisibility::Visible);
	}

	if (InnerCheckBox)
	{
		InnerCheckBox->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UObjectiveListItemWidget::SetAsCompleted() const
{
	OuterCheckBox->SetCheckedState(ECheckBoxState::Checked);
	InnerCheckBox->SetCheckedState(ECheckBoxState::Checked);
}

void UObjectiveListItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	const UGameObjectiveListItem* Objective { CastChecked<UGameObjectiveListItem>(ListItemObject) };

	// If this is a sub-goal show the inner checkbox and vice-versa
	OuterCheckBox->SetVisibility(Objective->GetData().IsSubGoal ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	InnerCheckBox->SetVisibility(Objective->GetData().IsSubGoal ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);

	FText Text { Objective->GetData().DisplayText };
	ObjectiveText->SetText(Objective->GetData().DisplayText);
}
