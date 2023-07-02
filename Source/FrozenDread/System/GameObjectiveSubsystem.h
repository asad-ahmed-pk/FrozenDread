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

	/** Add the given objective to the list of objectives */
	UFUNCTION(BlueprintPure=false, Category="Objectives")
	void AddObjective(const FGameObjective& Objective) const;

	/** Mark the given objective as complete */
	UFUNCTION(BlueprintPure=false, Category="Objectives")
	void CompleteObjective(const FGameObjective& Objective) const;

private:
	UObjectiveWidget* Widget { nullptr };
};
