//
// GameObjectiveSubsystem.cpp
// Implementation of the UGameObjectiveSubsystem class.
//

#include "FrozenDread/System/GameObjectiveSubsystem.h"

#include "FrozenDread/UI/ObjectiveWidget.h"

void UGameObjectiveSubsystem::Setup(UObjectiveWidget* ObjectiveWidget)
{
	Widget = ObjectiveWidget;
}

void UGameObjectiveSubsystem::AddObjective(const FGameObjective& Objective) const
{
	if (Widget != nullptr)
	{
		Widget->AddObjective(Objective);
	}
}

void UGameObjectiveSubsystem::CompleteObjective(const FGameObjective& Objective) const
{
	if (Widget != nullptr)
	{
		Widget->MarkObjectiveCompleted(Objective.ID);
	}
}
