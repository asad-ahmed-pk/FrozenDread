//
// KeyCard.h
// Definition of the AKeyCard class.
//

#pragma once

#include "CoreMinimal.h"

#include "FrozenDread/Gameplay/GameItems.h"
#include "FrozenDread/Gameplay/InteractiveObject.h"
#include "FrozenDread/Gameplay/InventoryItem.h"

#include "KeyCard.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class FROZENDREAD_API AKeyCard : public AInventoryItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKeyCard();

	// AInventoryItem overrides
	FORCEINLINE virtual EGameItemType GetGameItemType() override { return EGameItemType::KeyCard; }
	FORCEINLINE virtual int32 GetItemID() override { return static_cast<int32>(KeyCardID); }

private:
	/** The static mesh to use for the key card */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Rendering", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	/** The box component that triggers the interaction system */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBoxComponent> InteractionBox;

	/** The ID of this key card */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	EKeyCardID KeyCardID { EKeyCardID::None };
};
