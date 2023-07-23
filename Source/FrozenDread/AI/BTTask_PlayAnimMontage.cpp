//
// BTTask_PlayAnimMontage.cpp
// Implementation of the UBTTask_PlayAnimMontage class.
//

#include "BTTask_PlayAnimMontage.h"

#include "AIController.h"
#include "GameFramework/Character.h"

FString UBTTask_PlayAnimMontage::GetStaticDescription() const
{
	return TEXT("Play selected animation montage");
}

EBTNodeResult::Type UBTTask_PlayAnimMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	check(AnimMontage);

	const AAIController* Owner { OwnerComp.GetOwner<AAIController>() };
	const ACharacter* Pawn { CastChecked<ACharacter>(Owner->GetCharacter()) };

	const float MontageLength { Pawn->GetMesh()->GetAnimInstance()->Montage_Play(AnimMontage) };
	if (MontageLength > 0.0F)
	{
		// Trigger timer to end task (end of montage)
		OwnerBTComp = &OwnerComp;
		GetWorld()->GetTimerManager().SetTimer(CompletionTimer, this, &UBTTask_PlayAnimMontage::MontageCompleted, MontageLength);
		return EBTNodeResult::InProgress;
	}
	
	return EBTNodeResult::Failed;
}

void UBTTask_PlayAnimMontage::MontageCompleted()
{
	FinishLatentTask(*OwnerBTComp, EBTNodeResult::Succeeded);
}
