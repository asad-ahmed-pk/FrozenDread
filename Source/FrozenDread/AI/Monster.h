//
// Monster.cpp
// Implementation of the AMonster class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

class UEnvironmentDataComponent;

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
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

	FORCEINLINE UEnvironmentDataComponent* GetEnvironmentDataComponent() const { return EnvironmentDataComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UEnvironmentDataComponent> EnvironmentDataComponent;
};
