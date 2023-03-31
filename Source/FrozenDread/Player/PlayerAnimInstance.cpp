//
// PlayerAnimInstance.cpp
// Implementation of the UPlayerAnimInstance class.
//

#include "FrozenDread/Player/PlayerAnimInstance.h"

#include "FrozenDread/Player/PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

constexpr double MIN_GROUND_SPEED_TO_MOVE { 3.0 };


void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Cache player character reference
	if (AActor* Owner { GetOwningActor() }) {
		PlayerCharacter = CastChecked<APlayerCharacter>(Owner);
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (PlayerCharacter.IsValid())
	{
		// Update anim parameters
		const UCharacterMovementComponent* MovementComponent { CastChecked<UCharacterMovementComponent>(PlayerCharacter->GetMovementComponent()) };

		// Movement
		const FVector Velocity { MovementComponent->Velocity };
		const FVector GroundVelocity { Velocity.X, Velocity.Y, 0.0 };
		const double GroundSpeed { GroundVelocity.Length() };
		const double Acceleration { MovementComponent->GetCurrentAcceleration().Length() };

		ShouldMove = (GroundSpeed > MIN_GROUND_SPEED_TO_MOVE && Acceleration > 0.0);
		
		// Falling
		IsFalling = MovementComponent->IsFalling();
	}
}

