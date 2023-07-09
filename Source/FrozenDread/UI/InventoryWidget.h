//
// InventoryWidget.h
// Definition of the UInventoryWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "FrozenDread/Player/Inventory.h"

#include "InventoryWidget.generated.h"

class AInventoryItem;
class UTileView;
class UTextBlock;
class UButton;
class UInventoryItemWidget;
class USoundBase;

/**
 * UMG Widget for presenting the player's inventory.
 */
UCLASS()
class FROZENDREAD_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Subscribe to the given inventory item added event */
	void SubscribeToEvent(FInventoryItemAddedEvent& Event) const;

protected:
	virtual void NativeConstruct() override;

protected:
	/** The tile view that shows the inventory items */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTileView> ItemTileView;

	/** The title of the item currently being displayed */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentSelectionTitle;

	/** The description of the item currently being displayed */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentSelectionDescription;

	/** Close button to close the inventory */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> CloseButton;

private:
	/** The sound to play when the user hovers over an item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sound", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundBase> HoverSound;

	/** The sound to play when the user selects an item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sound", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundBase> SelectionSound;

private:
    UInventoryItemWidget* CurrentSelectedItemWidget { nullptr };
};
