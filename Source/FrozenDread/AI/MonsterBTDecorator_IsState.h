//
// MonsterBTDecorator_IsState.h
// Definition of the UMonsterBTDecorator_IsState class.
//

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MonsterBTDecorator_IsState.generated.h"

enum class EMonsterState : uint8;

/**
 * Compares the monster state to the given state and returns true if equal.
 */
UCLASS()
class FROZENDREAD_API UMonsterBTDecorator_IsState : public UBTDecorator
{
	GENERATED_BODY()

public:
	UMonsterBTDecorator_IsState();

protected:
	virtual FString GetStaticDescription() const override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	/** The state to check the current monster state against */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess="true"))
	EMonsterState State;
};
