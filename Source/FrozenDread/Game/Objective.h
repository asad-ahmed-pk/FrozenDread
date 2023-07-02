//
// Objective.h
// Definition of the objective struct
//

#pragma once

#include "Engine/DataTable.h"

#include "Objective.generated.h"

/**
 * Represents a game objective that the player must complete to advance the game.
 */
USTRUCT(BlueprintType)
struct FGameObjective : public FTableRowBase
{
	GENERATED_BODY()
	
	// The unique ID of the objective
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ID { 0 };

	// The ID of the parent goal (this value is ignored if IsSubGoal is false)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ParentID { 0 };

	// True if this is a sub-goal
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSubGoal { false };

	// The text that will be displayed in the UI for the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayText;

	bool operator==(const FGameObjective& Other) const { return ID == Other.ID; }
};

/** List item UObject that wraps a FGameObjective for use in Widgets */
UCLASS()
class UGameObjectiveListItem : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetObjective(const FGameObjective& Objective) { GameObjective = Objective; }
	FORCEINLINE const FGameObjective& GetData() const { return GameObjective; }

private:
	FGameObjective GameObjective{};
};