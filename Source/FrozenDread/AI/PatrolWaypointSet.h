//
// APatrolWaypointSet.h
// Definition of the APatrolWaypointSet class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolWaypointSet.generated.h"

class USplineComponent;

/**
 * Represents a set of waypoints for the AI to use as patrolling behaviour.
 */
UCLASS()
class FROZENDREAD_API APatrolWaypointSet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APatrolWaypointSet();

	/** The current total number of waypoints */
	int32 GetNumPoints() const;

	/** Get the location of the waypoint at the given index */
	FVector GetWaypointLocation(int32 Index) const;

private:
	/** The spline used to represent waypoints */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Waypoints", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USplineComponent> Spline;
};
