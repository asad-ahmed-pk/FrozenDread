//
// InventoryItem.h
// Definition of the AInventoryItem class.
//

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "MetasoundSource.h"

#include "FrozenDread/Gameplay/GameItems.h"
#include "FrozenDread/Gameplay/InteractiveObject.h"

#include "InventoryItem.generated.h"

class UMetaSoundSource;
class UTexture2D;

UCLASS()
class FROZENDREAD_API AInventoryItem : public AActor, public IInteractiveObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInventoryItem();

	/** Return the type of this inventory item */
	virtual EGameItemType GetGameItemType() { return EGameItemType::Default; }

	/** Return the unique ID for this item for its item type */
	virtual int32 GetItemID() { return -1; }

	// IInteractiveObject implementation
	virtual void SetHighlighted(bool IsHighlighted) override {}
	virtual FText DisplayText() const override { return InteractionText; }
	virtual void Interact(APlayerCharacter* PlayerCharacter) override;

	// Getters
	FORCEINLINE FText GetTitleText() const { return TitleText; }
	FORCEINLINE FText GetDescriptionText() const { return DescriptionText; }
	UTexture2D* GetInventoryIcon() const { return InventoryIcon; }

private:
	/** The text to display as the title of the item in the inventory */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	FText TitleText;

	/** The text to display as the description of the item in the inventory */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true", MultiLine="true"))
	FText DescriptionText;

	/** The icon to use in the inventory */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UTexture2D> InventoryIcon;

	/** The text to display whe the player looks at the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	FText InteractionText;

	/** The sound to play when the player picks up the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UMetaSoundSource> InteractionSound;
};
