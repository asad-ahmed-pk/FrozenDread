//
// UBTTask_Monster_GoToWaypoint.cpp
// Implementation of the UBTTask_Monster_GoToWaypoint class.
//

#include "FrozenDread/AI/BTTask_Monster_GoToWaypoint.h"
#include "FrozenDread/AI/Monster.h"
#include "FrozenDread/AI/PatrolWaypointSet.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Monster_GoToWaypoint::UBTTask_Monster_GoToWaypoint()
{
	NodeName = TEXT("Go to waypoint");
	BlackboardKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Monster_GoToWaypoint, BlackboardKey));
}

FString UBTTask_Monster_GoToWaypoint::GetStaticDescription() const
{
	return FString::Printf(TEXT("Go to waypoint index in: %s"), *BlackboardKey.SelectedKeyName.ToString());
}

EBTNodeResult::Type UBTTask_Monster_GoToWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get controlled monster
	AAIController* Controller { OwnerComp.GetAIOwner() };
	const AMonster* Monster { CastChecked<AMonster>(Controller->GetPawn()) };

	// Get the location of the waypoint from the monster and move there
	const int32 WaypointIndex { OwnerComp.GetBlackboardComponent()->GetValueAsInt(BlackboardKey.SelectedKeyName) };
	const FVector LocationToMove { Monster->GetPatrolWaypointSet()->GetWaypointLocation(WaypointIndex) };
	Controller->MoveToLocation(LocationToMove);

	// Update the blackboard key to the next index (or cycle back to first)
	const int32 NumWaypoints { Monster->GetPatrolWaypointSet()->GetNumPoints() };
	const int32 NextWaypointIndex { WaypointIndex + 1 < NumWaypoints ? WaypointIndex + 1 : 0 };
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(BlackboardKey.SelectedKeyName, NextWaypointIndex);

	// Complete task
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}

void UBTTask_Monster_GoToWaypoint::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTTask_Monster_GoToWaypoint::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}
