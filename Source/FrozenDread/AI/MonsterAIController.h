//
// AMonsterAIController.h
// Definition of the AMonsterAIController class.
//

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "MonsterAIController.generated.h"

struct FAIStimulus;

class AMonster;
class APlayerCharacter;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UBehaviorTreeComponent;
class UBehaviorTree;
class APatrolWaypointSet;

/**
 * AI controller class for the game monster.
 */
UCLASS()
class FROZENDREAD_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	/** Default constructor */
	AMonsterAIController();

	/** Return the team attitude towards the given actor */
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	/** The controlled monster is in the player's flash light range / cone */
	void MonsterIsInFlashLightCone(APlayerCharacter* PlayerCharacter);

	/** Set the waypoints that the controller will make the pawn follow */
	FORCEINLINE void SetWaypoints(APatrolWaypointSet* WaypointSet) { Waypoints = WaypointSet; }

	/** Get the waypoints that the controlled pawn is following */
	FORCEINLINE APatrolWaypointSet* GetWaypoints() const { return Waypoints; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnSightPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);

	AActor* GetPerceivedPlayerCharacter() const;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Perception", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

private:
	AMonster* Monster { nullptr };
	FVector LastKnownPlayerLocation;
	TTuple<float, float> DefaultSightRadiusSettings;
	APatrolWaypointSet* Waypoints { nullptr };
};
