//
// Dialogue.h
// Definition of the FDialogueItem struct
//

#pragma once

#include "Engine/DataTable.h"

#include "Dialogue.generated.h"

/**
 * Represents a single dialogue item that is to be played.
 */
USTRUCT(BlueprintType)
struct FDialogueItem : public FTableRowBase
{
	GENERATED_BODY()

	/** The ID of the dialogue item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ID;

	/** The text of the dialogue */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText;

	FORCEINLINE bool operator==(const FDialogueItem& Other) const { return ID == Other.ID; }
};