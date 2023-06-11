//
// MonsterBTService_SetWorldObjects.h
// Definition of the UMonsterBTService_SetWorldObjects class.
//

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MonsterBTService_SetWorldObjects.generated.h"

class UEnvironmentDataComponent;

/**
 * BT Service to query and set world objects of interest for the monster AI.
 */
UCLASS()
class FROZENDREAD_API UMonsterBTService_SetWorldObjects : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:
	UMonsterBTService_SetWorldObjects();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	virtual FString GetStaticServiceDescription() const override;
	virtual FString GetStaticDescription() const override;

private:
	TWeakObjectPtr<UEnvironmentDataComponent> EnvironmentDataComponent { nullptr };
};
