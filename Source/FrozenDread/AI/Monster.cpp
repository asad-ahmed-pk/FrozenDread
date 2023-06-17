//
// Monster.h
// Definition of the AMonster class.
//

#include "Monster.h"

#include "EnvironmentDataComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "FrozenDread/AI/MonsterAIController.h"

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

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	Controller = GetController<AMonsterAIController>();
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AMonster::OnMontageCompleted);
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonster::SetMonsterState(const EMonsterState& State)
{
	// Skip setting the state if there is no change
	if (MonsterState == State)
	{
		return;
	}

	switch (State)
	{
	case EMonsterState::Alerted:
		check(RageMontage);
		PlayAnimMontage(RageMontage);
		break;

	default:
		break;
	}
	
	MonsterState = State;
}

void AMonster::OnMontageCompleted(UAnimMontage* Montage, bool WasInterrupted)
{
	if (Montage == RageMontage)
	{
		check(Controller);
		Controller->MonsterRageCompleted();
	}
}
