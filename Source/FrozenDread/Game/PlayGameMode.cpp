//
// PlayGameMode.cpp
// Implementation of the APlayGameMode class.
//


#include "FrozenDread/Game/PlayGameMode.h"

#include "GameStatics.h"
#include "Kismet/GameplayStatics.h"

#include "FrozenDread/Gameplay/Door.h"
#include "FrozenDread/Level/MainLevelCoordinator.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/System/GameEventSubsystem.h"
#include "FrozenDread/System/PlayerDialogueSubsystem.h"
#include "FrozenDread/System/MusicPlayerSubsystem.h"
#include "FrozenDread/System/GameObjectiveSubsystem.h"

APlayGameMode::APlayGameMode()
{
	// Debug Cvars
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	IConsoleManager::Get().RegisterConsoleVariable(
		TEXT("game.debug.player.is_wearing_suit"),
		0,
		TEXT("Set to 1 to wear the exo suit."),
		ECVF_Cheat
	);
#endif
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetupSubsystems();
}

void APlayGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// Setup level coordinator based on the map
	check(LevelCoordinatorClass);
	AActor* LevelCoordinatorActor { GetWorld()->SpawnActor(LevelCoordinatorClass) };
	LevelCoordinator = Cast<ALevelCoordinator>(LevelCoordinatorActor);

	// Setup the game events
	SetupDoorInteractionEvents();
}

void APlayGameMode::SetupSubsystems()
{
	// Setup game event subsystem
	UGameEventSubsystem* EventSubsystem { GetWorld()->GetSubsystem<UGameEventSubsystem>() };
	check(EventSubsystem);
	EventSubsystem = EventSubsystem;
	APlayerCharacter* Player { CastChecked<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)) };
	EventSubsystem->Setup(Player);

	// Get dialogue subsystem
	UPlayerDialogueSubsystem* DialogueSubsystem { GetWorld()->GetSubsystem<UPlayerDialogueSubsystem>() };
	check(DialogueSubsystem);

	// Get objective subsystem
	UGameObjectiveSubsystem* ObjectiveSubsystem { GetWorld()->GetSubsystem<UGameObjectiveSubsystem>() };

	// Get music player subsystem
	UMusicPlayerSubsystem* MusicPlayerSubsystem { UGameStatics::GetMusicSubsystem(this) };
	check(MusicPlayerSubsystem);

	// Set the subsystems cache for the level coordinator for this level
	SubsystemCache = { EventSubsystem, ObjectiveSubsystem, DialogueSubsystem, MusicPlayerSubsystem };
	LevelCoordinator->Init(SubsystemCache);
}

void APlayGameMode::SetupDoorInteractionEvents()
{
	TArray<AActor*> Doors;
	UGameplayStatics::GetAllActorsOfClass(this, ADoor::StaticClass(), Doors);
	
	check(LevelCoordinator.IsValid());
	
	for (AActor* Actor : Doors)
	{
		if (ADoor* Door { Cast<ADoor>(Actor) })
		{
			Door->OnDoorInteractedWith.AddUObject(LevelCoordinator.Get(), &ALevelCoordinator::PlayerInteractedWithDoor);
		}
	}
}
