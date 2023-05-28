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
class UTexture2D;
class UImage;

/**
 * UMG Widget representing an item to display in the inventory
 */
UCLASS()
class FROZENDREAD_API UInventoryItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	/** Highlight or un-highlight this widget */
	void SetHighlighted(bool bIsHighlighted);
	
protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
	/** The title text of the item */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> TitleText;

	/** The image icon to use for the item */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> IconImage;

	/** The background image to use for the item */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> BackgroundImage;

private:
	/** The texture to use for the normal state of the item (not hovered) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UTexture2D> DefaultBackgroundTexture;

	/** The texture to use for the highlighted state of the item (hovered) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UTexture2D> HighlightedTexture;
};
