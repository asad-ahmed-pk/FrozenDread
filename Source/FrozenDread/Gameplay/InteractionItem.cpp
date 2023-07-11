//
// InteractionItem.cpp
// Implementation of the AInteractionItem class.
//

#include "FrozenDread/Gameplay/InteractionItem.h"

#include "Components/BoxComponent.h"

// Sets default values
AInteractionItem::AInteractionItem()
{
	// Scene Component
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);
	
	// Box Component
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());
	
	// Other settings
	PrimaryActorTick.bCanEverTick = false;
}

void AInteractionItem::Interact(APlayerCharacter* PlayerCharacter)
{
	// Notify the level script that this actor was interacted with
	OnInteractedWith.Broadcast();
}

void AInteractionItem::SetHighlighted(bool IsHighlighted)
{
	// Do nothing as this is a generic item
}

FText AInteractionItem::DisplayText() const
{
	return InteractionText;
}

