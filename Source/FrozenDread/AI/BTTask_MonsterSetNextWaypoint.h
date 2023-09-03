//
// BTTask_MonsterSetNextWaypoint.h
// Definition of the UBTTask_MonsterSetNextWaypoint class.
//

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MonsterSetNextWaypoint.generated.h"

/**
 * Get and set the next waypoint for the monster.
 */
UCLASS()
class FROZENDREAD_API UBTTask_MonsterSetNextWaypoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	/** Constructor for the BT Task */
	UBTTask_MonsterSetNextWaypoint();

	/** Execute this BT Task */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	/** The key that will be updated with the next waypoint location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties", meta=(AllowPrivateAccess="true"))
	FBlackboardKeySelector LocationKey;

	/** The key that will be updated with the next waypoint index */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties", meta=(AllowPrivateAccess="true"))
	FBlackboardKeySelector WaypointIndexKey;
};
