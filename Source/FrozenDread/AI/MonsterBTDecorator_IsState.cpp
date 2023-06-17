//
// MonsterBTDecorator_IsState.cpp
// Implementation of the UMonsterBTDecorator_IsState class.
//

#include "FrozenDread/AI/MonsterBTDecorator_IsState.h"

#include "AIController.h"
#include "FrozenDread/AI/Monster.h"

UMonsterBTDecorator_IsState::UMonsterBTDecorator_IsState()
{
	NodeName = TEXT("Compare Monster State");
}

FString UMonsterBTDecorator_IsState::GetStaticDescription() const
{
	const TEnumAsByte StateEnum { State };
	return FString::Printf(TEXT("Check if monster state is %s"), *UEnum::GetValueAsString(StateEnum.GetValue()));
}

void UMonsterBTDecorator_IsState::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UMonsterBTDecorator_IsState::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

bool UMonsterBTDecorator_IsState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AMonster* Monster { CastChecked<AMonster>(OwnerComp.GetAIOwner()->GetPawn()) };
	return (State == Monster->GetMonsterState());
}
