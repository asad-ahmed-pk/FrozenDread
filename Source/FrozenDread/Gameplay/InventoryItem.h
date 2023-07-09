//
// InventoryItem.h
// Definition of the AInventoryItem class.
//

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "MetasoundSource.h"
#include "Engine/DataTable.h"

#include "FrozenDread/Gameplay/GameItems.h"
#include "FrozenDread/Gameplay/InteractiveObject.h"

#include "InventoryItem.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UMetaSoundSource;
class UTexture2D;

USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
	GENERATED_BODY()

	// The unique ID of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ID;

	// The display title in the inventory for the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Title;

	// The description text for the item in the inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	// The Icon to use for the item in the inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon;
};

UCLASS()
class FROZENDREAD_API AInventoryItem : public AActor, public IInteractiveObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInventoryItem();

	virtual void BeginPlay() override;

	/** Get the Inventory info for this item */
	const FInventoryItemInfo& GetInventoryInfo() const { return CachedItemInfo; }

	// IInteractiveObject implementation
	virtual void SetHighlighted(bool IsHighlighted) override;
	virtual FText DisplayText() const override { return InteractionText; }
	virtual void Interact(APlayerCharacter* PlayerCharacter) override;

private:
	/** The data table row corresponding to this inventory item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true", RequiredAssetDataTags="RowStructure=/Script/FrozenDread.InventoryItemInfo"))
	FDataTableRowHandle InventoryItemInfo;
	
	/** The text to display whe the player looks at the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	FText InteractionText;

	/** The sound to play when the player picks up the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UMetaSoundSource> InteractionSound;

	/** The mesh to use for the item in the world */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Rendering", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	/** The box component that triggers the interaction system */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBoxComponent> InteractionBox;

	/** The highlight material to use when the player is looking at the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UMaterialInterface> HighlightMaterial;

private:
	FInventoryItemInfo CachedItemInfo{};
};
