//
// BTTask_MonsterSetState.cpp
// Implementation of the UBTTask_MonsterSetState class.
//

#include "BTTask_MonsterSetState.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FrozenDread/AI/Monster.h"

UBTTask_MonsterSetState::UBTTask_MonsterSetState()
{
	NodeName = TEXT("Set Monster State");
	BlackboardKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_MonsterSetState, BlackboardKey), StaticEnum<EMonsterState>());
}

EBTNodeResult::Type UBTTask_MonsterSetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Update blackboard key
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(BlackboardKey.SelectedKeyName, static_cast<uint8>(NewState));

	// Update Monster character
	const AAIController* Controller { OwnerComp.GetAIOwner() };

	AMonster* Monster = CastChecked<AMonster>(Controller->GetPawn());
	check(Monster);

	Monster->SetMonsterState(NewState);

	// Complete task
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

void UBTTask_MonsterSetState::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

FString UBTTask_MonsterSetState::GetStaticDescription() const
{
	return FString::Printf(TEXT("Set Monster State To: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
