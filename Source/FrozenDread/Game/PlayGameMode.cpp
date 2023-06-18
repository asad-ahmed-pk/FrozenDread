//
// PlayGameMode.cpp
// Implementation of the APlayGameMode class.
//


#include "FrozenDread/Game/PlayGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "FrozenDread/Game/GameTags.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/System/GameEventSubsystem.h"

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

	// Setup game event subsystem
	UGameEventSubsystem* EventSubsystem { GetWorld()->GetSubsystem<UGameEventSubsystem>() };
	check(EventSubsystem);

	APlayerCharacter* Player { CastChecked<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)) };

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(this, GameTag::MONSTER, Actors);

	// Expecting only 1 tag
	check(Actors.Num() == 1);
	AMonster* Monster { CastChecked<AMonster>(Actors[0]) };
	
	EventSubsystem->Setup(Player, Monster);
}
