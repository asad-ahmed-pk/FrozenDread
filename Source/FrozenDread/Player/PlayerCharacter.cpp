//
// PlayerCharacter.cpp
// Implementation of the APlayerCharacter class.
//

#include "PlayerCharacter.h"

#include "FrozenDread/Game/GameTags.h"
#include "FrozenDread/Gameplay/InteractionComponent.h"
#include "FrozenDread/Player/GamePlayerController.h"
#include "FrozenDread/Player/FlashLightComponent.h"
#include "FrozenDread/AI/Monster.h"
#include "FrozenDread/AI/MonsterAIController.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

//////////////////////////////////////////////// UE FUNCTIONS ////////////////////////////////////////////////

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Capsule setup
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Controller setup
	bUseControllerRotationYaw = true;

	// Character movement config
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Camera attached to head socket
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MainCamera->SetupAttachment(GetMesh(), TEXT("head"));

	// Interaction component
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction Component"));
	AddOwnedComponent(InteractionComponent);

	// Perception stimuli source
	PerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("PerceptionStimuliComponent"));
	PerceptionStimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
	PerceptionStimuliSource->RegisterWithPerceptionSystem();

	// Spring arm for flashlight
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComponent"));
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->TargetArmLength = 0;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraLagSpeed = 10.0F;
	SpringArmComponent->SetupAttachment(MainCamera);

	// Flashlight component
	FlashLightComponent = CreateDefaultSubobject<UFlashLightComponent>(TEXT("FlashLightComponent"));
	FlashLightComponent->SetupAttachment(SpringArmComponent);

	// Player Tag
	Tags.Add(GameTag::PLAYER);

	// Other settings
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if monster is in the player's flashlight
	check(FlashLightComponent);
	if (AActor* Actor { FlashLightComponent->GetActorInRange() })
	{
		const AMonster* Monster { CastChecked<AMonster>(Actor) };
		Monster->GetController<AMonsterAIController>()->MonsterIsInFlashLightCone(this);
	}
}

//////////////////////////////////////////////// INPUT ////////////////////////////////////////////////

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		// Use Action
		EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Use);

		// Flashlight toggle action
		EnhancedInputComponent->BindAction(FlashLightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ToggleFlashLight);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// Get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Use(const FInputActionValue& Value)
{
	InteractionComponent->InteractWithCurrentItem();
}

void APlayerCharacter::ToggleFlashLight(const FInputActionValue& Value)
{
	check(FlashLightComponent);
	FlashLightComponent->Toggle();
}

//////////////////////////////////////////////// OTHER ////////////////////////////////////////////////

UInventory* APlayerCharacter::GetInventory() const
{
	const AGamePlayerController* PlayerController { GetController<AGamePlayerController>() };
	check(PlayerController);
	return PlayerController->GetInventory();
}
