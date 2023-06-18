//
// Monster.cpp
// Implementation of the AMonster class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

class UEnvironmentDataComponent;
class UAnimMontage;
class AMonsterAIController;
class UCharacterMovementComponent;

/** Enum for representing the monster's state */
UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle					UMETA(DisplayName = "Idle"),
	Feeding					UMETA(DisplayName = "Feeding"),
	Alerted					UMETA(DisplayName = "Alerted"),
	HuntingPlayer			UMETA(DisplayName = "Hunting Player"),
	Searching				UMETA(DisplayName = "Searching")
};

/**
 * Represents the monster character.
 */
UCLASS()
class FROZENDREAD_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

	/** Set the monster state */
	UFUNCTION(BlueprintCallable)
	void SetMonsterState(const EMonsterState& State);

	/** Get a reference to the environment data component */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UEnvironmentDataComponent* GetEnvironmentDataComponent() const { return EnvironmentDataComponent; }

	/** Get a reference to the monster's current state */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EMonsterState GetMonsterState() const { return MonsterState; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnMontageCompleted(UAnimMontage* Montage, bool WasInterrupted);

private:
	/** The component that queries for data in the monster's surroundings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UEnvironmentDataComponent> EnvironmentDataComponent;

	/** The montage to use for the rage animation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAnimMontage> RageMontage;

	/** The default speed of the monster when not chasing the player */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float DefaultMovementSpeed { 300.0F };

	/** The max speed that can be reached when chasing the player */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float MaxHuntingSpeed { 500.0F };
	
	/** The increase in movement speed per second when the monster is hunting the player */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float HuntingSpeedGainPerSecond { 5.0F };


private:
	EMonsterState MonsterState { EMonsterState::Idle };
	AMonsterAIController* Controller { nullptr };
	UCharacterMovementComponent* MovementComponent { nullptr };
};

