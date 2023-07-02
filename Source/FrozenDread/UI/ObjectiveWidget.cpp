//
// ObjectiveWidget.cpp
// Implementation of the UObjectiveWidget class.
//

#include "FrozenDread/UI/ObjectiveWidget.h"

#include "ObjectiveListItemWidget.h"
#include "Algo/IndexOf.h"
#include "Components/ListView.h"

void UObjectiveWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ObjectiveListView)
	{
		ObjectiveListView->SetSelectionMode(ESelectionMode::None);
	}

	bIsFocusable = false;
}

void UObjectiveWidget::AddObjective(const FGameObjective& Objective) const
{
	// Create ListItem with this objective and add it to the list view
	UGameObjectiveListItem* ListItem { NewObject<UGameObjectiveListItem>() };
	ListItem->SetObjective(Objective);
	ObjectiveListView->AddItem(ListItem);
}

void UObjectiveWidget::MarkObjectiveCompleted(uint8 ObjectiveID) const
{
	// Find the list item and mark it as completed
	auto ListItems { ObjectiveListView->GetListItems() };
	const auto Index = Algo::IndexOfByPredicate(ListItems, [ObjectiveID](UObject* Item)
	{
		const UGameObjectiveListItem* ObjectiveListItem { CastChecked<UGameObjectiveListItem>(Item) };
		return ObjectiveListItem->GetData().ID == ObjectiveID;
	});

	const UObject* ListItem { ObjectiveListView->GetItemAt(Index) };
	const auto EntryWidget { CastChecked<UObjectiveListItemWidget>(ObjectiveListView->GetEntryWidgetFromItem(ListItem)) };
	EntryWidget->SetAsCompleted();
}

