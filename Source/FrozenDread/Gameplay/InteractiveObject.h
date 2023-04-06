//
// InteractiveObject.h
// Definition of the IInteractiveObject interface.
//

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveObject.generated.h"

class APlayerCharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractiveObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for an object that the player can interact with in some way.
 */
class FROZENDREAD_API IInteractiveObject
{
	GENERATED_BODY()

public:
	/** Highlight this item since the player is looking at it. */
	virtual void SetHighlighted(bool IsHighlighted) = 0;

	/** The player has interacted with the item */
	virtual void Interact(APlayerCharacter* PlayerCharacter) = 0;

	/** The display text to show when the player looks at the object. */
	virtual FText DisplayText() const = 0;
};
