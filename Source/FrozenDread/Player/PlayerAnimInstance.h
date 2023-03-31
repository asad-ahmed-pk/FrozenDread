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
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	TWeakObjectPtr<APlayerCharacter> PlayerCharacter { nullptr };

	bool ShouldMove { false };
	bool IsFalling { false };
};
