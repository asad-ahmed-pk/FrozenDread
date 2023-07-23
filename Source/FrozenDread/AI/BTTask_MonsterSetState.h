//
// BTTask_MonsterSetState.h
// Definition of the UBTTask_MonsterSetState class.
//

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTTask_MonsterSetState.generated.h"

enum class EMonsterState : uint8;

/**
 * Blackboard Task for updating the monster's state.
 */
UCLASS()
class FROZENDREAD_API UBTTask_MonsterSetState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_MonsterSetState();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual FString GetStaticDescription() const override;

private:
	/** The new state to set for the monster and the BB */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Search", meta=(AllowPrivateAccess="true"))
	EMonsterState NewState;
};
