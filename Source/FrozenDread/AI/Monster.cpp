//
// Monster.h
// Definition of the AMonster class.
//

#include "Monster.h"

#include "EnvironmentDataComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "FrozenDread/AI/MonsterAnimInstance.h"

// Sets default values
AMonster::AMonster()
{
	// Capsule setup
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Character movement config
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Environment data component
	EnvironmentDataComponent = CreateDefaultSubobject<UEnvironmentDataComponent>(TEXT("Environment Data Component"));
	
	// Other settings
	PrimaryActorTick.bCanEverTick = true;
}

void AMonster::SetMonsterState(const EMonsterState& State)
{
	// Skip setting the state if there is no change
	if (MonsterState == State)
	{
		return;
	}

	UMonsterAnimInstance* AnimInstance { CastChecked<UMonsterAnimInstance>(GetMesh()->GetAnimInstance()) };
	
	switch (State)
	{
	case EMonsterState::Feeding:
		AnimInstance->StartFeeding();
		break;

	case EMonsterState::Alerted:
		if (MonsterState == EMonsterState::Feeding)
		{
			// Notify anim instance to transition to end feeding animation
			AnimInstance->StopFeeding();
		}
		else
		{
			// Nothing to do for the other cases
		}
		break;

	case EMonsterState::HuntingPlayer:
		if (MonsterState == EMonsterState::Feeding)
		{
			// Notify anim instance to transition to end feeding animation
			AnimInstance->StopFeeding();
		}
		break;

	default:
		break;
	}

	MonsterState = State;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

