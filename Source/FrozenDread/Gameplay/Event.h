//
// Event.h
// Definition of gameplay events
//

#pragma once

class AInventoryItem;

// TODO: Consider removing this since there is only 1 event declared here
namespace Event
{
	namespace Inventory
	{
		// Item was added to the player's inventory
		DECLARE_MULTICAST_DELEGATE_OneParam(FInventoryItemAddedEvent, AInventoryItem*);
	}
}