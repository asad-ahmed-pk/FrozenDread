//
// BTTask_PlayAnimMontage.h
// Definition of the UBTTask_PlayAnimMontage class.
//

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PlayAnimMontage.generated.h"

class UAnimMontage;

/**
 * Task for playing an animation montage on the given pawn
 */
UCLASS()
class FROZENDREAD_API UBTTask_PlayAnimMontage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	void MontageCompleted();

private:
	/** The animation montage to play */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAnimMontage> AnimMontage;

private:
	UBehaviorTreeComponent* OwnerBTComp { nullptr };
	FTimerHandle CompletionTimer;
};
