//
// GameObjectiveSubsystem.cpp
// Implementation of the UGameObjectiveSubsystem class.
//

#include "FrozenDread/System/GameObjectiveSubsystem.h"

#include "FrozenDread/UI/ObjectiveWidget.h"

void UGameObjectiveSubsystem::Setup(UObjectiveWidget* ObjectiveWidget)
{
	Widget = ObjectiveWidget;

	// Add any pending objectives since subsystem can be init before widget
	for (const FGameObjective& Objective : PendingObjectives)
	{
		AddObjective(Objective);
	}
}

bool UGameObjectiveSubsystem::IsObjectiveAdded(const FGameObjective& Objective) const
{
	return CurrentObjectives.Contains(Objective.ID);
}

void UGameObjectiveSubsystem::AddObjective(const FGameObjective& Objective)
{
	if (Widget != nullptr)
	{
		Widget->AddObjective(Objective);
		CurrentObjectives.Add(Objective.ID, false);
	}
	else
	{
		PendingObjectives.Add(Objective);
	}
}

void UGameObjectiveSubsystem::CompleteObjective(const FGameObjective& Objective)
{
	if (Widget != nullptr)
	{
		Widget->MarkObjectiveCompleted(Objective.ID);
		check(CurrentObjectives.Contains(Objective.ID));
		CurrentObjectives[Objective.ID] = true;
	}
}
