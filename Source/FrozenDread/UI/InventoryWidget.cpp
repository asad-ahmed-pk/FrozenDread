//
// InventoryWidget.cpp
// Implementation of the UInventoryWidget class.
//

#include "InventoryWidget.h"

#include "Components/TileView.h"

#include "FrozenDread/Gameplay/InventoryItem.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::AddInventoryItem(AInventoryItem* InventoryItem) const
{
	ItemTileView->AddItem(InventoryItem);
}

void UInventoryWidget::SubscribeToEvent(Event::Inventory::FInventoryItemAddedEvent& Event) const
{
	Event.AddLambda([this](AInventoryItem* InventoryItem)
	{
		AddInventoryItem(InventoryItem);
	});
}
