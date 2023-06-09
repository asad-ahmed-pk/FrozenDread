//
// MonsterAnimInstance.cpp
// Implementation of the UMonsterAnimInstance class.
//

#include "FrozenDread/AI/MonsterAnimInstance.h"

#include "FrozenDread/AI/Monster.h"

#include "GameFramework/CharacterMovementComponent.h"

constexpr double MIN_GROUND_SPEED_TO_MOVE { 3.0 };

void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// Cache reference to monster
	if (AActor* Owner { GetOwningActor() }) {
		Monster = CastChecked<AMonster>(Owner);
	}
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Monster.IsValid()) {
		return;
	}

	// Movement
	const UCharacterMovementComponent* MovementComponent { CastChecked<UCharacterMovementComponent>(Monster->GetMovementComponent()) };

	const FVector Velocity { MovementComponent->Velocity };
	const FVector GroundVelocity { Velocity.X, Velocity.Y, 0.0 };
	const double Acceleration { MovementComponent->GetCurrentAcceleration().Length() };

	GroundSpeed  =  GroundVelocity.Length();
	ShouldMove = (GroundSpeed > MIN_GROUND_SPEED_TO_MOVE);
}