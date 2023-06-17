//
// AMonsterAIController.cpp
// Implementation of the AMonsterAIController class.
//

#include "FrozenDread/AI/MonsterAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "FrozenDread/AI/Monster.h"
#include "FrozenDread/AI/BlackboardKeys.h"
#include "FrozenDread/Player/PlayerCharacter.h"

AMonsterAIController::AMonsterAIController()
{
	// Setup behaviour tree and blackboard
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviour Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));

	// Perception component
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponment"));

	// Default sight settings
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 2000.0F;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.0F;
	SightConfig->PeripheralVisionAngleDegrees = 90.0F;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
	PerceptionComponent->ConfigureSense(*SightConfig);
}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	// Cache ref to monster character
	Monster = CastChecked<AMonster>(GetPawn());

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

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnSightPerceptionUpdate);
}

void AMonsterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// Update the player's location if monster is currently hunting the player
	if (Monster && Monster->GetMonsterState() == EMonsterState::HuntingPlayer)
	{
		check(PerceptionComponent);

		// The only actor the monster can chase is the player in this game
		// safe to assume this is the player
		TArray<AActor*> Actors;
		PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), Actors);
		if (Actors.Num() > 0)
		{
			const FVector TargetLocation { Actors[0]->GetActorLocation() };
			GetBlackboardComponent()->SetValueAsVector(BlackBoardKey::TARGET_LOCATION, TargetLocation);
		}
	}
}

void AMonsterAIController::OnSightPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		APlayerCharacter* Player { Cast<APlayerCharacter>(Actor) };
		if (Player != nullptr)
		{
			Monster->SetMonsterState(EMonsterState::HuntingPlayer);
			GetBlackboardComponent()->SetValueAsVector(BlackBoardKey::TARGET_LOCATION, Player->GetActorLocation());
			SetFocus(Player);
		}
	}
	else
	{
		SetFocus(nullptr);
		Monster->SetMonsterState(EMonsterState::Searching);
	}
}

