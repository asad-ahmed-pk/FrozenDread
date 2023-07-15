//
// InventoryItem.cpp
// Implementation of the AInventoryItem class.
//

#include "InventoryItem.h"

#include "FrozenDread/Player/Inventory.h"
#include "FrozenDread/Player/PlayerCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInventoryItem::AInventoryItem()
{
	// Root Component
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootSceneComponent);
	
	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	// Interaction Box
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	InteractionBox->SetupAttachment(RootComponent);
	
	// Other settings
	PrimaryActorTick.bCanEverTick = false;
}

void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();

	// Cache the item info
	const FInventoryItemInfo* Item { InventoryItemInfo.GetRow<FInventoryItemInfo>("InventoryInfo") };
	check(Item);
	CachedItemInfo = *Item;
}

void AInventoryItem::SetHighlighted(bool IsHighlighted)
{
	check(Mesh);
	check(HighlightMaterial);
	Mesh->SetOverlayMaterial(IsHighlighted ? HighlightMaterial : nullptr);
}

void AInventoryItem::Interact(APlayerCharacter* PlayerCharacter)
{
	// Get the player's inventory and add this item to the inventory
	check(PlayerCharacter);

	// Add to inventory
	UInventory* Inventory { PlayerCharacter->GetInventory() };
	const FInventoryItemInfo* ItemInfo { InventoryItemInfo.GetRow<FInventoryItemInfo>("Interaction") };
	Inventory->AddItemToInventory(ItemInfo);

	// Play pickup sound
	check(InteractionSound);
	UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, GetActorLocation());

	// Notify delegates
	OnPickedUp.Broadcast();

	// Remove from game world
	Destroy();
}
