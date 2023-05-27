//
// InventoryItemWidget.h
// Definition of the UInventoryItemWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "InventoryItemWidget.generated.h"

class UTextBlock;
class UImage;

/**
 * UMG Widget representing an item to display in the inventory
 */
UCLASS()
class FROZENDREAD_API UInventoryItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
	/** The title text of the item */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> TitleText;

	/** The image icon to use for the item*/
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> IconImage;
};
