//
// Inventory.cpp
// Implementation of the UInventory class.
//

#include "FrozenDread/Player/Inventory.h"
#include "FrozenDread/Game/InventoryItemInfo.h"

void UInventory::AddItemToInventory(const FInventoryItemInfo* ItemInfo)
{
	UInventoryEntry* Entry { NewObject<UInventoryEntry>(this) };
	Entry->SetItemInfo(ItemInfo);
	Items.Add(Entry);
	InventoryItemAddedEvent.Broadcast(Entry);
}

bool UInventory::HasItem(uint8 ID) const
{
	for (const auto Item : Items)
	{
		if (Item && Item->GetItemInfo().ID == ID)
		{
			return true;
		}
	}

	return false;
}
