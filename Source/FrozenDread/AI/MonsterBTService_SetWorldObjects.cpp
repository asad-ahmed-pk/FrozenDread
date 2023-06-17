//
// MonsterBTService_SetWorldObjects.cpp
// Implementation of the UMonsterBTService_SetWorldObjects class.
//

#include "FrozenDread/AI/MonsterBTService_SetWorldObjects.h"

#include "AIController.h"
#include "Algo/MinElement.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "FrozenDread/AI/BlackboardKeys.h"
#include "FrozenDread/AI/Monster.h"
#include "FrozenDread/AI/EnvironmentDataComponent.h"

UMonsterBTService_SetWorldObjects::UMonsterBTService_SetWorldObjects()
{
	
}

void UMonsterBTService_SetWorldObjects::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	// Cache the monster's environment data comp
	const AAIController* AIController { SearchData.OwnerComp.GetAIOwner() };
	const AMonster* Monster { CastChecked<AMonster>(AIController->GetPawn()) };
	EnvironmentDataComponent = Monster->GetEnvironmentDataComponent();
}

void UMonsterBTService_SetWorldObjects::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UMonsterBTService_SetWorldObjects::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

FString UMonsterBTService_SetWorldObjects::GetStaticServiceDescription() const
{
	return TEXT("Sets relevant world objects for the Monster AI BB.");
}

FString UMonsterBTService_SetWorldObjects::GetStaticDescription() const
{
	return TEXT("Set World Objects Service");
}

void UMonsterBTService_SetWorldObjects::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Get all corpse locations
	check(EnvironmentDataComponent.IsValid());
	const TArray<FVector>& Locations { EnvironmentDataComponent->GetCorpseLocations() };

	// Determine the closest one
	const FVector MonsterLocation { OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation() };
	const FVector* CorpseLocation = Algo::MinElementBy<>(Locations, [&MonsterLocation](const FVector& Location)
	{
		const double Distance { (Location - MonsterLocation).Length() };
		return Distance;
	});

	if (CorpseLocation)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackBoardKey::CLOSEST_CORPSE_KEY_NAME, *CorpseLocation);
	}
}


