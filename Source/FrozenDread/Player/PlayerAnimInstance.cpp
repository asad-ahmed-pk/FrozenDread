//
// PlayerAnimInstance.cpp
// Implementation of the UPlayerAnimInstance class.
//

#include "FrozenDread/Player/PlayerAnimInstance.h"

#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/Player/GamePlayerState.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"

constexpr double MIN_PLAYER_GROUND_SPEED_TO_MOVE { 3.0 };

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// Cache player character reference
	if (AActor* Owner { GetOwningActor() }) {
		PlayerCharacter = CastChecked<APlayerCharacter>(Owner);
	}
}

void UPlayerAnimInstance::PlayFootStepSound()
{
	check(PlayerCharacter.IsValid());
	check(WalkingSound);

	const FVector PlayerLocation { PlayerCharacter->GetActorLocation() };
	FFindFloorResult FloorResult;
	PlayerCharacter->GetCharacterMovement()->FindFloor(PlayerLocation, FloorResult, true);
	const FVector SoundOriginLocation { PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z + FloorResult.FloorDist };

	UGameplayStatics::PlaySoundAtLocation(this, WalkingSound, SoundOriginLocation);
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (PlayerCharacter.IsValid())
	{
		// Movement
		const UCharacterMovementComponent* MovementComponent { CastChecked<UCharacterMovementComponent>(PlayerCharacter->GetMovementComponent()) };

		const FVector Velocity { MovementComponent->Velocity };
		const FVector GroundVelocity { Velocity.X, Velocity.Y, 0.0 };
		const double Acceleration { MovementComponent->GetCurrentAcceleration().Length() };

		GroundSpeed  =  GroundVelocity.Length();
		ShouldMove = (GroundSpeed > MIN_PLAYER_GROUND_SPEED_TO_MOVE && Acceleration > 0.0);
		
		// Falling
		IsFalling = MovementComponent->IsFalling();
	}
}
