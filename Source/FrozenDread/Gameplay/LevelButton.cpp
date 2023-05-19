//
// LevelButton.cpp
// Implementation of the ALevelButton class.
//

#include "FrozenDread/Gameplay/LevelButton.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelButton::ALevelButton()
{
	// Collision box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetCollisionObjectType(CollisionChannel);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(CollisionChannel, ECollisionResponse::ECR_Block);
	RootComponent = BoxComponent;
	
	// ExoSuit mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxComponent);
	
	// Other settings
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ALevelButton::BeginPlay()
{
	Super::BeginPlay();
}


void ALevelButton::SetHighlighted(bool IsHighlighted)
{
	
}

FText ALevelButton::DisplayText() const
{
	return InteractionText;
}

void ALevelButton::Interact(APlayerCharacter* PlayerCharacter)
{
	if (IsInCoolDown)
	{
		return;
	}
	
	// Broadcast to delegate
	OnButtonPressed.Broadcast();

	// Play sound
	check(InteractionSound);
	const FVector Location { GetActorLocation() };
	const FRotator Rotation { GetActorRotation() };
	UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, Location, Rotation);

	// Start the cooldown timer so player cannot spam the button
	IsInCoolDown = true;
	GetWorldTimerManager().SetTimer(CoolDownTimerHandle, this, &ALevelButton::CoolDownCompleted, CoolDownTimeSeconds, false);
}

