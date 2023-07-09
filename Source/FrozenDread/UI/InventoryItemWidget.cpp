//
// InventoryItemWidget.cpp
// Implementation of the UInventoryItemWidget class.
//

#include "FrozenDread/UI/InventoryItemWidget.h"
#include "FrozenDread/Game/InventoryItemInfo.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInventoryItemWidget::SetHighlighted(bool bIsHighlighted)
{
	// if already selected then ignore
	check(DefaultBackgroundTexture);
	check(HighlightedTexture);

	const FSlateBrush Brush { UWidgetBlueprintLibrary::MakeBrushFromTexture(bIsHighlighted ? HighlightedTexture : DefaultBackgroundTexture) };
	BackgroundImage->SetBrush(Brush);
}

void UInventoryItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	const UInventoryEntry* Entry { CastChecked<UInventoryEntry>(ListItemObject) };
	const FInventoryItemInfo& ItemInfo { Entry->GetItemInfo() };
	
	TitleText->SetText(ItemInfo.Title);

	UTexture2D* Texture { ItemInfo.Icon };
	const FSlateBrush Brush { UWidgetBlueprintLibrary::MakeBrushFromTexture(Texture) };
	IconImage->SetBrush(Brush);
}
