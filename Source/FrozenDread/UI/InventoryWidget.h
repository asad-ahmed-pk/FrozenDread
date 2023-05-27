//
// InventoryWidget.h
// Definition of the UInventoryWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "FrozenDread/Gameplay/Event.h"

#include "InventoryWidget.generated.h"

class AInventoryItem;
class UTileView;

/**
 * UMG Widget for presenting the player's inventory.
 */
UCLASS()
class FROZENDREAD_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Add the given inventory item data to this widget */
	void AddInventoryItem(AInventoryItem* InventoryItem) const;

	/** Subscribe to the given inventory item added event */
	void SubscribeToEvent(Event::Inventory::FInventoryItemAddedEvent& Event) const;

protected:
	virtual void NativeConstruct() override;

protected:
	/** The tile view that shows the inventory items */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTileView> ItemTileView;

	/** The title of the item currently being displayed */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	FText CurrentSelectionTitle;

	/** The description of the item currently being displayed */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	FText CurrentSelectionDescription;
};
