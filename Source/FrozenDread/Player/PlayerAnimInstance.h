//
// PlayerAnimInstance.h
// Definition of the UPlayerAnimInstance class.
//

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class APlayerCharacter;

/**
 * Animation instance for the player.
 */
UCLASS()
class FROZENDREAD_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeBeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	bool ShouldMove { false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	bool IsFalling { false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	double GroundSpeed { 0.0 };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Suit", meta=(AllowPrivateAccess = "true"))
	bool IsWearingExoSuit { false };

private:
	TWeakObjectPtr<APlayerCharacter> PlayerCharacter { nullptr };
};
