//
// InventoryItemWidget.cpp
// Implementation of the UInventoryItemWidget class.
//

#include "InventoryItemWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "FrozenDread/Gameplay/InventoryItem.h"

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
	const AInventoryItem* Item { CastChecked<AInventoryItem>(ListItemObject) };
	
	TitleText->SetText(Item->GetTitleText());

	UTexture2D* Texture { Item->GetInventoryIcon() };
	const FSlateBrush Brush { UWidgetBlueprintLibrary::MakeBrushFromTexture(Texture) };
	IconImage->SetBrush(Brush);
}
