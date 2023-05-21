//
// InventoryItem.h
// Definition of the AInventoryItem class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FrozenDread/Gameplay/GameItems.h"

#include "InventoryItem.generated.h"

UCLASS()
class FROZENDREAD_API AInventoryItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInventoryItem();

	/** Return the type of this inventory item */
	virtual EGameItemType GetGameItemType() { return EGameItemType::Default; }

	/** Return the unique ID for this item for its item type */
	virtual int32 GetItemID() { return -1; }

private:
	/** The text to display as the title of the item in the inventory */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	FText TitleText;

	/** The text to display as the description of the item in the inventory */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	FText DescriptionText;
};
