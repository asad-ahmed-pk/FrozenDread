//
// UBTTask_Monster_GoToWaypoint.h
// Definition of the UBTTask_Monster_GoToWaypoint class.
//

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Monster_GoToWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class FROZENDREAD_API UBTTask_Monster_GoToWaypoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Monster_GoToWaypoint();

protected:
	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
};
