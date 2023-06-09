//
// MonsterBTTask_FindRandomLocation.h
// Definition of the UMonsterBTTask_FindRandomLocation class.
//

#include "FrozenDread/AI/MonsterBTTask_FindRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UMonsterBTTask_FindRandomLocation::UMonsterBTTask_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");

	// Only accept vectors for the key
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UMonsterBTTask_FindRandomLocation, BlackboardKey));
}

EBTNodeResult::Type UMonsterBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	// Get the monster character
	AAIController* AIController { OwnerComp.GetAIOwner() };
	const APawn* AIPawn { AIController->GetPawn() };

	// Get pawn origin
	const FVector Origin { AIPawn->GetActorLocation() };

	// Use nav system
	const UNavigationSystemV1* NavSystem { UNavigationSystemV1::GetCurrent(GetWorld()) };
	if (NavSystem != nullptr && NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	// Complete task
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}

FString UMonsterBTTask_FindRandomLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}

void UMonsterBTTask_FindRandomLocation::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
