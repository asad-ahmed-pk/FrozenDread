//
// MonsterAnimInstance.h
// Definition of the UMonsterAnimInstance class.
//

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

class AMonster;
class UAnimMontage;

enum class EMonsterState : uint8;

/**
 * Animation instance for the game's monster. 
 */
UCLASS()
class FROZENDREAD_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/** Start the feeding animation */
	void StartFeeding();

	/** Stop feeding animation */
	void StopFeeding();

	UFUNCTION(BlueprintCallable, Category="State")
	EMonsterState GetMonsterState() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	bool ShouldMove { false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	double GroundSpeed { 0.0 };

	/** The montage to use for the feeding animations */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAnimMontage> FeedingAnimMontage;

private:
	TWeakObjectPtr<AMonster> Monster { nullptr };
};
