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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UEnvironmentDataComponent> EnvironmentDataComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAnimMontage> RageMontage;

private:
	EMonsterState MonsterState { EMonsterState::Idle };
	AMonsterAIController* Controller { nullptr };
};

