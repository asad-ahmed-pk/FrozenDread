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
#include "FrozenDread/Game/GameTags.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/System/GameEventSubsystem.h"

constexpr float CHASE_SIGHT_RADIUS_INCREASE_FACTOR { 2.0F };

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
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	PerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
	PerceptionComponent->ConfigureSense(*SightConfig);
}

ETeamAttitude::Type AMonsterAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (Other.ActorHasTag(GameTag::PLAYER))
	{
		return ETeamAttitude::Hostile;
	}
	
	return ETeamAttitude::Neutral;
}

void AMonsterAIController::MonsterIsInFlashLightCone(APlayerCharacter* PlayerCharacter)
{
	check(Monster);
	const EMonsterState MonsterState { Monster->GetMonsterState() };
	if (MonsterState == EMonsterState::Patrolling || MonsterState == EMonsterState::Searching)
	{
		SetFocus(PlayerCharacter);
	}
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Cache ref to monster character
	Monster = CastChecked<AMonster>(GetPawn());

	// Cache default sight radius settings
	DefaultSightRadiusSettings.Get<0>() = SightConfig->SightRadius;
	DefaultSightRadiusSettings.Get<1>() = SightConfig->LoseSightRadius;

	// Run behaviour tree
	check(BehaviorTree);
	RunBehaviorTree(BehaviorTree.Get());
	BehaviorTreeComponent->StartTree(*BehaviorTree.Get());

	if (Blackboard && BehaviorTree)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset);
	}

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnSightPerceptionUpdate);
}

void AMonsterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// Update the player's location if monster is currently chasing the player
	if (Monster && Monster->GetMonsterState() == EMonsterState::ChasingPlayer)
	{
		if (const AActor* Player = GetPerceivedPlayerCharacter())
		{ 
			const FVector TargetLocation { Player->GetActorLocation() };
			GetBlackboardComponent()->SetValueAsVector(BlackBoardKey::TARGET_LOCATION, TargetLocation);
		}
	}
}

void AMonsterAIController::OnSightPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		APlayerCharacter* Player { CastChecked<APlayerCharacter>(Actor) };
		
		Monster->SetMonsterState(EMonsterState::ChasingPlayer);
		GetBlackboardComponent()->SetValueAsObject(BlackBoardKey::TARGET_PLAYER, Player);
		SetFocus(Player);
		
		SightConfig->SightRadius = DefaultSightRadiusSettings.Get<0>() * CHASE_SIGHT_RADIUS_INCREASE_FACTOR;
		SightConfig->LoseSightRadius = DefaultSightRadiusSettings.Get<1>() * CHASE_SIGHT_RADIUS_INCREASE_FACTOR;

		UGameEventSubsystem* GameEventSubsystem { GetWorld()->GetSubsystem<UGameEventSubsystem>() };
		GameEventSubsystem->PlayerIsBeingChased(true);
	}
	else
	{
		SetFocus(nullptr);
		GetBlackboardComponent()->SetValueAsVector(BlackBoardKey::TARGET_LOCATION, Actor->GetActorLocation());
		GetBlackboardComponent()->ClearValue(BlackBoardKey::TARGET_PLAYER);
		
		Monster->SetMonsterState(EMonsterState::Searching);

		SightConfig->SightRadius = DefaultSightRadiusSettings.Get<0>();
		SightConfig->LoseSightRadius = DefaultSightRadiusSettings.Get<1>();

		UGameEventSubsystem* GameEventSubsystem { GetWorld()->GetSubsystem<UGameEventSubsystem>() };
		GameEventSubsystem->PlayerIsBeingChased(true);
	}

	PerceptionComponent->ConfigureSense(*SightConfig);

	LastKnownPlayerLocation = Actor->GetActorLocation();
}

AActor* AMonsterAIController::GetPerceivedPlayerCharacter() const
{
	check(PerceptionComponent);

	// The only actor the monster can chase is the player in this game
	// safe to assume this is the player
	TArray<AActor*> Actors;
	PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), Actors);
	if (Actors.Num() > 0)
	{
		return Actors[0];
	}

	return nullptr;
}

