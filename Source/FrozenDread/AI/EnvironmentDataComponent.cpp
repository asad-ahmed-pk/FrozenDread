//
// EnvironmentDataComponent.cpp
// Implementation of the UEnvironmentDataComponent class.
//

#include "EnvironmentDataComponent.h"

#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UEnvironmentDataComponent::UEnvironmentDataComponent()
{
	// Other settings
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UEnvironmentDataComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get the locations of the corpses in the level
	CacheCorpseLocations();
}

void UEnvironmentDataComponent::CacheCorpseLocations()
{
	check(CorpseTag.IsValid());
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(this, CorpseTag.GetTagName(), Actors);

	CorpseLocations.Reserve(Actors.Num());
	Algo::Transform(Actors, CorpseLocations, [](const AActor* Actor)
	{
		return Actor->GetActorLocation();
	});
}
