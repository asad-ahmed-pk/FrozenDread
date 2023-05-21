//
// InventoryItem.cpp
// Implementation of the AInventoryItem class.
//

#include "InventoryItem.h"

#include "FrozenDread/Player/Inventory.h"
#include "FrozenDread/Player/PlayerCharacter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AInventoryItem::AInventoryItem()
{
	// Other settings
	PrimaryActorTick.bCanEverTick = false;
}

void AInventoryItem::Interact(APlayerCharacter* PlayerCharacter)
{
	// Get the player's inventory and add this item to the inventory
	check(PlayerCharacter);

	// Add to inventory
	UInventory* Inventory { PlayerCharacter->GetInventory() };
	Inventory->AddItemToInventory(this);

	// Play pickup sound
	check(InteractionSound);
	UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, GetActorLocation());

	// Remove from game world
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}
