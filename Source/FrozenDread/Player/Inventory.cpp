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

bool UInventory::HasItem(EGameItemType ItemType, uint8 ID) const
{
	for (const auto& Item : Items)
	{
		if (Item.IsValid() && Item->GetGameItemType() == ItemType && Item->GetItemID() == static_cast<int32>(ID))
		{
			return true;
		}
	}

	return false;
}
