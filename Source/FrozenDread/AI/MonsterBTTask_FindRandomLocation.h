//
// MonsterBTTask_FindRandomLocation.cpp
// Implementation of the UMonsterBTTask_FindRandomLocation class.
//

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MonsterBTTask_FindRandomLocation.generated.h"

/**
 * Task for finding a random location on the nav mesh
 */
UCLASS()
class FROZENDREAD_API UMonsterBTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMonsterBTTask_FindRandomLocation();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Search", meta=(AllowPrivateAccess="true"))
	float SearchRadius { 500.0F };
};
