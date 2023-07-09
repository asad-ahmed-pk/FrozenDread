//
// Inventory.h
// Definition of the UInventory class.
//

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "Inventory.generated.h"

class UInventoryEntry;
struct FInventoryItemInfo;

// Item was added to the player's inventory
DECLARE_MULTICAST_DELEGATE_OneParam(FInventoryItemAddedEvent, UInventoryEntry*);

/**
 * Represents the player's inventory.
 */
UCLASS()
class FROZENDREAD_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	/** Add the given inventory entry with the given info to this inventory */
	void AddItemToInventory(const FInventoryItemInfo* ItemInfo);

	/** Query inventory system to see if the player has the given item of ID */
	UFUNCTION(BlueprintPure=false, Category="Inventory")
	bool HasItem(uint8 ID) const;

	/** Get a reference to the InventoryItemAddedEvent */
	FORCEINLINE FInventoryItemAddedEvent& GetInventoryItemAddedEvent() { return InventoryItemAddedEvent; }
	
private:
	TArray<TObjectPtr<UInventoryEntry>> Items;
	FInventoryItemAddedEvent InventoryItemAddedEvent;
};
