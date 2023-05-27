//
// Event.h
// Definition of gameplay events
//

#pragma once

class AInventoryItem;

namespace Event
{
	namespace Inventory
	{
		// Item was added to the player's inventory
		DECLARE_MULTICAST_DELEGATE_OneParam(FInventoryItemAddedEvent, AInventoryItem*);
	}
}