//
// AMonsterAIController.cpp
// Implementation of the AMonsterAIController class.
//

#include "FrozenDread/AI/MonsterAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonsterAIController::AMonsterAIController()
{
	// Setup behaviour tree and blackboard
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviour Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	// Run behaviour tree
	check(BehaviorTree);
	RunBehaviorTree(BehaviorTree.Get());
	BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (Blackboard && BehaviorTree)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset);
	}
}
