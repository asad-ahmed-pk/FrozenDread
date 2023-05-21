//
// Inventory.cpp
// Implementation of the UInventory class.
//

#include "Inventory.h"

#include "FrozenDread/Gameplay/InventoryItem.h"

void UInventory::AddItemToInventory(TSharedPtr<AInventoryItem> InventoryItemComponent)
{
	Items.Add(InventoryItemComponent);
}

bool UInventory::HasItem(EGameItemType ItemType, uint8 ID)
{
	for (const auto& Item : Items)
	{
		if (Item->GetGameItemType() == ItemType && Item->GetItemID() == static_cast<int32>(ID))
		{
			return true;
		}
	}

	return false;
}
