//
// Monster.h
// Definition of the AMonster class.
//

#include "Monster.h"

#include "BlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "FrozenDread/Game/GameStatics.h"
#include "FrozenDread/Game/GameTags.h"
#include "FrozenDread/System/GameEventSubsystem.h"
#include "Kismet/GameplayStatics.h"

const FName EYES_SOCKET_NAME { "Eyes_Socket" };

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
	
	// Other settings
	PrimaryActorTick.bCanEverTick = true;
}

void AMonster::Init()
{
	// Override the movement component settings
	MovementComponent->MaxWalkSpeed = DefaultMovementSpeed;
}

void AMonster::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = GetMesh()->GetSocketLocation(EYES_SOCKET_NAME);
	OutRotation = GetMesh()->GetSocketRotation(EYES_SOCKET_NAME);
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	Init();
	MakeGrowlSound();
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If chasing the player, increase speed every tick
	if (MonsterState == EMonsterState::ChasingPlayer || MonsterState == EMonsterState::Searching)
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

	// Set movement speed back to normal if not hunting player
	if (State == EMonsterState::Patrolling || State == EMonsterState::Idle)
	{
		MovementComponent->MaxWalkSpeed = DefaultMovementSpeed;
	}
	
	MonsterState = State;

	// Notify blackboard that state was updated
	UBlackboardComponent* BlackboardComponent { UGameStatics::GetCharacterBlackBoardComponent(this) };
	check(BlackboardComponent);
	BlackboardComponent->SetValueAsEnum(BlackBoardKey::MONSTER_STATE, static_cast<uint8>(MonsterState));

	// Notify game event subsystem if monster is chasing the player or not
	const bool PlayerIsChased { MonsterState == EMonsterState::ChasingPlayer || MonsterState == EMonsterState::Searching };
	UGameEventSubsystem* GameEventSubsystem { GetWorld()->GetSubsystem<UGameEventSubsystem>() };
	GameEventSubsystem->PlayerIsBeingChased(PlayerIsChased);
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

void AMonster::MakeGrowlSound()
{
	const UAnimInstance* AnimInstance { GetMesh()->GetAnimInstance() };
	check(AnimInstance);
	
	if (!AnimInstance->IsAnyMontagePlaying())
	{
		check(GrowlSound);
		UGameplayStatics::PlaySoundAtLocation(this, GrowlSound, GetActorLocation(), GetActorRotation(), 1, 1, 0, SoundAttenuationSettings);
	}

	// Set timer for next growl sound play
	const float Time { FMath::RandRange(GrowlRandomIntervalRange.X, GrowlRandomIntervalRange.Y) };
	GetWorld()->GetTimerManager().SetTimer(GrowlSoundTimerHandle, this, &AMonster::MakeGrowlSound, Time);
}
