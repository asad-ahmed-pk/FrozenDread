//
// Inventory.cpp
// Implementation of the UInventory class.
//

#include "Inventory.h"

#include "FrozenDread/Gameplay/InventoryItem.h"

void UInventory::AddItemToInventory(AInventoryItem* InventoryItem)
{
	Items.Add(InventoryItem);
	InventoryItemAddedEvent.Broadcast(InventoryItem);
}

bool UInventory::HasItem(uint8 ID) const
{
	for (const auto& Item : Items)
	{
		if (Item.IsValid() && Item->GetInventoryInfo().ID == ID)
		{
			return true;
		}
	}

	return false;
}
