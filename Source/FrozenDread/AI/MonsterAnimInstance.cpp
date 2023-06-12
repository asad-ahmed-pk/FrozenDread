//
// MonsterAnimInstance.cpp
// Implementation of the UMonsterAnimInstance class.
//

#include "FrozenDread/AI/MonsterAnimInstance.h"

#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "FrozenDread/AI/Monster.h"

static constexpr double MIN_GROUND_SPEED_TO_MOVE { 3.0 };

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

	GroundSpeed  =  GroundVelocity.Length();
	ShouldMove = (GroundSpeed > MIN_GROUND_SPEED_TO_MOVE);
}

void UMonsterAnimInstance::StartFeeding()
{
	check(FeedingAnimMontage);
	
	Montage_Stop(0.1F);
	Montage_Play(FeedingAnimMontage);
	Montage_JumpToSection(FName(TEXT("Start")), FeedingAnimMontage);
}

void UMonsterAnimInstance::StopFeeding()
{
	check(FeedingAnimMontage);
	Montage_JumpToSection(FName(TEXT("Stop")), FeedingAnimMontage);
}

EMonsterState UMonsterAnimInstance::GetMonsterState() const
{
	check(Monster.IsValid());
	return Monster->GetMonsterState();
}
