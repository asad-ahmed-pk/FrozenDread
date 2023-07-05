//
// InventoryWidget.cpp
// Implementation of the UInventoryWidget class.
//

#include "InventoryWidget.h"

#include "Components/TextBlock.h"
#include "Components/TileView.h"
#include "Kismet/GameplayStatics.h"

#include "FrozenDread/Gameplay/InventoryItem.h"
#include "FrozenDread/UI/InventoryItemWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemTileView)
	{
		// Ensure only single selection is allowed
		ItemTileView->SetSelectionMode(ESelectionMode::Single);
		
		// Handler for clicking on any item
		ItemTileView->OnItemClicked().AddLambda([this](UObject* ListItem)
		{
			// Set title and description for the selected entry
			const AInventoryItem* Item { Cast<AInventoryItem>(ListItem) };
			check(Item);
			const FInventoryItemInfo& ItemInfo { Item->GetInventoryInfo() };
			CurrentSelectionTitle->SetText(ItemInfo.Title);
			CurrentSelectionDescription->SetText(ItemInfo.Description);

			// Set it as highlighted
			UInventoryItemWidget* ItemWidget { CastChecked<UInventoryItemWidget>(ItemTileView->GetEntryWidgetFromItem(ListItem)) };
			ItemWidget->SetHighlighted(true);

			// Play selection sound
			check(SelectionSound);
			UGameplayStatics::PlaySound2D(this, SelectionSound);

			// De-select previous selected widget
			if (CurrentSelectedItemWidget)
			{
				CurrentSelectedItemWidget->SetHighlighted(false);
			}

			CurrentSelectedItemWidget = ItemWidget;
		});

		// Set item as highlighted / un-highlighted based on hover
		ItemTileView->OnItemIsHoveredChanged().AddLambda([this](UObject* ListItem, bool IsHovered)
		{
			UInventoryItemWidget* ItemWidget { CastChecked<UInventoryItemWidget>(ItemTileView->GetEntryWidgetFromItem(ListItem)) };

			// If this item is currently selected then ensure it remains highlighted
			// regardless if the mouse is no longer hovering over it
			if (ItemTileView->GetSelectedItem<UObject>() == ListItem)
			{
				ItemWidget->SetHighlighted(true);
			}
			else
			{
				ItemWidget->SetHighlighted(IsHovered);
			}

			// Play sound when hovered over only
			if (IsHovered)
			{
				check(HoverSound);
				UGameplayStatics::PlaySound2D(this, HoverSound);
			}
		});
	}
}

void UInventoryWidget::AddInventoryItem(AInventoryItem* InventoryItem) const
{
	ItemTileView->AddItem(InventoryItem);
}

void UInventoryWidget::SubscribeToEvent(FInventoryItemAddedEvent& Event) const
{
	Event.AddLambda([this](AInventoryItem* InventoryItem)
	{
		AddInventoryItem(InventoryItem);
	});
}
