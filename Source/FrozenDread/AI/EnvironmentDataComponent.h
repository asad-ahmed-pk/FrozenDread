//
// EnvironmentDataComponent.h
// Definition of the UEnvironmentDataComponent class.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"

#include "EnvironmentDataComponent.generated.h"

/**
 * Component that stores data of the environment. For use with AI.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FROZENDREAD_API UEnvironmentDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnvironmentDataComponent();

	// Getter for getting the corpse locations
	FORCEINLINE const TArray<FVector>& GetCorpseLocations() const { return CorpseLocations; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void CacheCorpseLocations();

private:
	/** The tag for the corpses for the monster to feed on */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Locations", meta=(AllowPrivateAccess="true"))
	FGameplayTag CorpseTag;

private:
	TArray<FVector> CorpseLocations;
};
