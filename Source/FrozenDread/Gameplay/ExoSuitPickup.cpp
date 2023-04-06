//
// ExoSuitPickup.cpp
// Implementation of the AExoSuitPickup class.
//

#include "FrozenDread/Gameplay/ExoSuitPickup.h"

#include "FrozenDread/Player/GamePlayerController.h"
#include "FrozenDread/Player/PlayerCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MetasoundSource.h"

// --------------------------------------------- UE Functions --------------------------------------------- //


// Sets default values
AExoSuitPickup::AExoSuitPickup()
{
	// Collision box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetCollisionObjectType(CollisionChannel);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(CollisionChannel, ECollisionResponse::ECR_Block);
	RootComponent = BoxComponent;
	
	// ExoSuit mesh
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ExoSuit Mesh"));
	Mesh->SetupAttachment(BoxComponent);
	
	// Other settings
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AExoSuitPickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AExoSuitPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// --------------------------------------------- IInteractiveObject --------------------------------------------- //

void AExoSuitPickup::SetHighlighted(bool IsHighlighted)
{
	// TODO: Implement highlight material
}

FText AExoSuitPickup::DisplayText() const
{
	return HighlightText;
}

void AExoSuitPickup::Interact(APlayerCharacter* PlayerCharacter)
{
	if (bPickedUp)
	{
		return;
	}
	
	check(PlayerCharacter);
	const AGamePlayerController* PlayerController { PlayerCharacter->GetController<AGamePlayerController>() };
	
	check(PlayerController)
	PlayerController->SwitchPlayerSuit();

	check(EquipSound);
	UGameplayStatics::PlaySound2D(this, EquipSound);

	bPickedUp = true;

	GetWorld()->DestroyActor(this);
}