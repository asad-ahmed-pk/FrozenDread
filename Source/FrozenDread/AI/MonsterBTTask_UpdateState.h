//
// MonsterBTTask_UpdateState.h
// Definition of the UMonsterBTTask_UpdateState class.
//

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "MonsterBTTask_UpdateState.generated.h"

enum class EMonsterState : uint8;

/**
 * Blackboard Task for updating the monster's state.
 */
UCLASS()
class FROZENDREAD_API UMonsterBTTask_UpdateState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMonsterBTTask_UpdateState();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual FString GetStaticDescription() const override;

private:
	/** The new state to set for the monster and the BB */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Search", meta=(AllowPrivateAccess="true"))
	EMonsterState NewState;
};
