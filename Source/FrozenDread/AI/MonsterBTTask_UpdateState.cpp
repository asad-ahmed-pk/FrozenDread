//
// MonsterBTTask_UpdateState.cpp
// Implementation of the UMonsterBTTask_UpdateState class.
//

#include "FrozenDread/AI/MonsterBTTask_UpdateState.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FrozenDread/AI/Monster.h"

UMonsterBTTask_UpdateState::UMonsterBTTask_UpdateState()
{
	NodeName = TEXT("Update Monster State");
	BlackboardKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UMonsterBTTask_UpdateState, BlackboardKey), StaticEnum<EMonsterState>());
}

EBTNodeResult::Type UMonsterBTTask_UpdateState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

void UMonsterBTTask_UpdateState::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

FString UMonsterBTTask_UpdateState::GetStaticDescription() const
{
	return FString::Printf(TEXT("Set Monster State To: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
