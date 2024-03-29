﻿//
// PlayGameMode.cpp
// Implementation of the APlayGameMode class.
//


#include "FrozenDread/Game/PlayGameMode.h"

#include "GameStatics.h"
#include "Engine/TriggerVolume.h"
#include "Kismet/GameplayStatics.h"

#include "FrozenDread/Gameplay/Door.h"
#include "FrozenDread/Gameplay/InteractionItem.h"
#include "FrozenDread/Gameplay/InventoryItem.h"
#include "FrozenDread/Level/MainLevelCoordinator.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/System/GameEventSubsystem.h"
#include "FrozenDread/System/PlayerDialogueSubsystem.h"
#include "FrozenDread/System/MusicPlayerSubsystem.h"
#include "FrozenDread/System/GameObjectiveSubsystem.h"

void APlayGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// Setup level coordinator based on the map
	check(LevelCoordinatorClass);
	AActor* LevelCoordinatorActor { GetWorld()->SpawnActor(LevelCoordinatorClass) };
	LevelCoordinator = Cast<ALevelCoordinator>(LevelCoordinatorActor);

	// Setup the game events
	SetupDoorInteractionEvents();
	SetupItemInteractionEvents();
	SetupTriggerEvents();
}

void APlayGameMode::StartPlay()
{
	Super::StartPlay();
	SetupSubsystems();
	check(LevelCoordinator.IsValid());
	LevelCoordinator->StartLevel();
}

void APlayGameMode::SetupSubsystems()
{
	// Setup game event subsystem
	UGameEventSubsystem* EventSubsystem { GetWorld()->GetSubsystem<UGameEventSubsystem>() };
	check(EventSubsystem);
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

void APlayGameMode::SetupItemInteractionEvents()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(this, UInteractiveObject::StaticClass(), Actors);

	check(LevelCoordinator.IsValid());

	for (AActor* Actor : Actors)
	{
		if (AInteractionItem* InteractionItem { Cast<AInteractionItem>(Actor) })
		{
			InteractionItem->OnInteractedWith.AddDynamic(LevelCoordinator.Get(), &ALevelCoordinator::PlayerInteractedWithItem);
		}
		else if (AInventoryItem* InventoryItem { Cast<AInventoryItem>(Actor) })
		{
			InventoryItem->OnPickedUp.AddDynamic(LevelCoordinator.Get(), &ALevelCoordinator::PlayerPickedUpItem);
		}
	}
}

void APlayGameMode::SetupTriggerEvents()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, ATriggerVolume::StaticClass(), Actors);

	check(LevelCoordinator.IsValid());
	
	for (AActor* Actor : Actors)
	{
		// Subscribe the current level coordinator to the volume's OnActorOverlap and OnActorEndOverlap events
		ATriggerVolume* TriggerVolume { CastChecked<ATriggerVolume>(Actor) };
		TriggerVolume->OnActorBeginOverlap.AddDynamic(LevelCoordinator.Get(), &ALevelCoordinator::OnTriggerVolumeBeginOverlap);
	}
}

