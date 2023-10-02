//
// GameObjectiveSubsystem.h
// Definition of the UGameObjectiveSubsystem class.
//

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "FrozenDread/Game/Objective.h"

#include "GameObjectiveSubsystem.generated.h"

class UObjectiveWidget;

/**
 * Subsystem for handling gameplay objectives and UI.
 */
UCLASS()
class FROZENDREAD_API UGameObjectiveSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/** Setup this sub system with the given objectives widget */
	void Setup(UObjectiveWidget* ObjectiveWidget);

	/** Returns true if the given objective has been added */
	bool IsObjectiveAdded(const FGameObjective& Objective) const;

	/** Add the given objective to the list of objectives */
	UFUNCTION(BlueprintPure=false, Category="Objectives")
	void AddObjective(const FGameObjective& Objective);

	/** Mark the given objective as complete */
	UFUNCTION(BlueprintPure=false, Category="Objectives")
	void CompleteObjective(const FGameObjective& Objective);

private:
	UObjectiveWidget* Widget { nullptr };
	TMap<uint8, bool> CurrentObjectives;
	TArray<FGameObjective> PendingObjectives;
};
