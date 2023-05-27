//
// Inventory.h
// Definition of the UInventory class.
//

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "FrozenDread/Gameplay/Event.h"
#include "FrozenDread/Gameplay/GameItems.h"
#include "FrozenDread/Gameplay/InventoryItem.h"

#include "Inventory.generated.h"

/**
 * Represents the player's inventory.
 */
UCLASS()
class FROZENDREAD_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	/** Add the given inventory item to this inventory */
	void AddItemToInventory(AInventoryItem* InventoryItem);

	/** Query inventory system to see if the player has the given item type of ID */
	bool HasItem(EGameItemType ItemType, uint8 ID) const;

	/** Get a reference to the InventoryItemAddedEvent */
	FORCEINLINE Event::Inventory::FInventoryItemAddedEvent& GetInventoryItemAddedEvent() { return InventoryItemAddedEvent; }
	
private:
	TArray<TWeakObjectPtr<AInventoryItem>> Items;
	Event::Inventory::FInventoryItemAddedEvent InventoryItemAddedEvent;
};
