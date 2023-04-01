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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess))
	bool ShouldMove { false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess))
	bool IsFalling { false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess))
	double GroundSpeed { 0.0 };

private:
	TWeakObjectPtr<APlayerCharacter> PlayerCharacter { nullptr };
};
