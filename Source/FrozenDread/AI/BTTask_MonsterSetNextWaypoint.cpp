//
// BTTask_MonsterSetNextWaypoint.cpp
// Implementation of the UBTTask_MonsterSetNextWaypoint class.
//


#include "FrozenDread/AI/BTTask_MonsterSetNextWaypoint.h"

#include "FrozenDread/AI/MonsterAIController.h"
#include "FrozenDread/AI/PatrolWaypointSet.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MonsterSetNextWaypoint::UBTTask_MonsterSetNextWaypoint()
{
	NodeName = TEXT("Set Next Waypoint For Monster");
}

EBTNodeResult::Type UBTTask_MonsterSetNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the patrol waypoint from the AI Controller
	AAIController* Controller { OwnerComp.GetAIOwner() };
	const AMonsterAIController* MonsterAIController { CastChecked<AMonsterAIController>(Controller) };
	const APatrolWaypointSet* Waypoints { MonsterAIController->GetWaypoints() };

	// Task fails if no waypoint is set on the AI controller
	if (Waypoints == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// Get the current waypoint index
	const int32 NumWaypoints { Waypoints->GetNumPoints() };
	const int32 WaypointIndex { OwnerComp.GetBlackboardComponent()->GetValueAsInt(WaypointIndexKey.SelectedKeyName) };
	const int32 NextWaypointIndex { WaypointIndex + 1 < NumWaypoints ? WaypointIndex + 1 : 0 };

	// Set the updated waypoint index and location to move to
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(WaypointIndexKey.SelectedKeyName, NextWaypointIndex);

	const FVector MoveToLocation { Waypoints->GetWaypointLocation(NextWaypointIndex) };
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(LocationKey.SelectedKeyName, MoveToLocation);

	// Task complete at this point
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
