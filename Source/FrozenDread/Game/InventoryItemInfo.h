//
// Inventory.h
// Definition of the Inventory Item Structs and UObjects.
//

#pragma once

#include "Engine/DataTable.h"

#include "InventoryItemInfo.generated.h"

/**
 * Represents info for an inventory item.
 */
USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
	GENERATED_BODY()

	// The unique ID of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ID;

	// The display title in the inventory for the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Title;

	// The description text for the item in the inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	// The Icon to use for the item in the inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon;
};

/**
 * Represents an entry for the player's inventory.
 * This is the UObject that wraps the DataTable handle.
 */
UCLASS()
class UInventoryEntry : public UObject
{
	GENERATED_BODY()
	
public:
	// Set this entry to use the given info
	FORCEINLINE void SetItemInfo(const FInventoryItemInfo* Info) { ItemInfo = Info; }

	// Get the item's info
	FORCEINLINE const FInventoryItemInfo& GetItemInfo() const { return *ItemInfo; }
	
private:
	const FInventoryItemInfo* ItemInfo { nullptr };
};