//
// PlayerAnimInstance.h
// Definition of the UPlayerAnimInstance class.
//

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MetasoundSource.h"

#include "PlayerAnimInstance.generated.h"

class APlayerCharacter;
class UMetaSoundSource;

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

	UFUNCTION(BlueprintCallable)
	void PlayFootStepSound();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	bool ShouldMove { false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	bool IsFalling { false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	double GroundSpeed { 0.0 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sounds", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UMetaSoundSource> WalkingSound;

private:
	TWeakObjectPtr<APlayerCharacter> PlayerCharacter { nullptr };
};
