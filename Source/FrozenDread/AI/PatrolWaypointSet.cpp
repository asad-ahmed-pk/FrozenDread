//
// APatrolWaypointSet.cpp
// Implementation of the APatrolWaypointSet class.
//


#include "PatrolWaypointSet.h"

#include "Components/SplineComponent.h"


// Sets default values
APatrolWaypointSet::APatrolWaypointSet()
{
	// Spline component
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("WaypointSpline"));
	
	// Other settings
	PrimaryActorTick.bCanEverTick = false;
}

int32 APatrolWaypointSet::GetNumPoints() const
{
	check(Spline);
	return Spline->GetNumberOfSplinePoints();
}

FVector APatrolWaypointSet::GetWaypointLocation(int32 Index) const
{
	check(Spline)
	return Spline->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
}


