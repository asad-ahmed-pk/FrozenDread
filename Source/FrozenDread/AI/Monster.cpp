//
// Monster.h
// Definition of the AMonster class.
//

#include "Monster.h"

#include "EnvironmentDataComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "FrozenDread/AI/MonsterAIController.h"
#include "FrozenDread/Game/GameTags.h"
#include "FrozenDread/System/GameEventSubsystem.h"

// Sets default values
AMonster::AMonster()
{
	// Capsule setup
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Character movement config
	MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed = DefaultMovementSpeed;
	MovementComponent->MinAnalogWalkSpeed = 20.f;
	MovementComponent->BrakingDecelerationWalking = 2000.f;

	// Sphere component
	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
	AttackSphere->SetSphereRadius(100.0F);
	AttackSphere->SetupAttachment(GetRootComponent());
	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnAttackSphereBeginOverlap);

	// Game tag
	Tags.Add(GameTag::MONSTER);

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

	// If chasing the player, increase speed every tick
	if (MonsterState == EMonsterState::HuntingPlayer)
	{
		check(MovementComponent);
		if (MovementComponent->MaxWalkSpeed <= MaxHuntingSpeed)
		{
			MovementComponent->MaxWalkSpeed += (DeltaTime * HuntingSpeedGainPerSecond);
		}
	}
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
	case EMonsterState::Idle:
		break;
	
	case EMonsterState::Alerted:
		check(RageMontage);
		PlayAnimMontage(RageMontage);
		break;

	case EMonsterState::Feeding:
		break;

	case EMonsterState::Searching:
		break;

	case EMonsterState::HuntingPlayer:
		break;
	}

	// Set movement speed back to normal if not hunting player
	if (State != EMonsterState::HuntingPlayer)
	{
		MovementComponent->MaxWalkSpeed = DefaultMovementSpeed;
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

void AMonster::OnAttackSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(GameTag::PLAYER))
	{
		// Report to the event subsystem that the player was caught
		const UGameEventSubsystem* EventSubsystem { GetWorld()->GetSubsystem<UGameEventSubsystem>() };
		check(EventSubsystem);
		EventSubsystem->PlayerWasCaught();
	}
}