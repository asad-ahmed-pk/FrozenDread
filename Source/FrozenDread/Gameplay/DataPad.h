//
// DataPad.h
// Definition of the ADataPad class.
//

#pragma once

#include "CoreMinimal.h"

#include "FrozenDread/Gameplay/InventoryItem.h"

#include "DataPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

/** Represents a data log that the player can read */
UCLASS()
class FROZENDREAD_API ADataPad : public AInventoryItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADataPad();

private:
	/** The mesh to display for the data-pad */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Rendering", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	/** The box component that triggers the interaction system */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBoxComponent> InteractionBox;
};
