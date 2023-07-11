//
// InteractionItem.h
// Definition of the AInteractionItem class.
//

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject.h"
#include "GameFramework/Actor.h"
#include "InteractionItem.generated.h"

class UBoxComponent;
class USceneComponent;

// Delegate for interaction with this item
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionDelegate);

/**
 * Represents an Actor that can be interacted with and triggers an interaction event.
 */
UCLASS()
class FROZENDREAD_API AInteractionItem : public AActor, public IInteractiveObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractionItem();

	// IInteractiveObject implementation

	// Interact with this actor
	virtual void Interact(APlayerCharacter* PlayerCharacter) override;

	// Set this actor to be highlighted
	virtual void SetHighlighted(bool IsHighlighted) override;

	// The display text to show when the player is looking at this actor
	virtual FText DisplayText() const override;

public:
	/** Called when the player interacts with this item */
	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FInteractionDelegate OnInteractedWith;

private:
	/** The text to display when the player looks at this actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	FText InteractionText;

	/** The root scene component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Scene", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> SceneComponent;
	
	/** The box component used to trigger interactions */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBoxComponent> BoxComponent;
};
