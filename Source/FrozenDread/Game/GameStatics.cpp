//
// GameStatics.cpp
// Implementation of the UGameStatics class.
//

#include "FrozenDread/Game/GameStatics.h"

#include "FrozenDread/Gameplay/GameLevelScriptActor.h"
#include "FrozenDread/System/MusicPlayerSubsystem.h"
#include "FrozenDread/Player/PlayerCharacter.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"

AGameLevelScriptActor* UGameStatics::GetLevelScript(const AActor* ContextActor)
{
	check(ContextActor);
	const ULevel* Level { ContextActor->GetWorld()->GetCurrentLevel() };
	check(Level);
	return CastChecked<AGameLevelScriptActor>(Level->LevelScriptActor);
}

UBlackboardComponent* UGameStatics::GetCharacterBlackBoardComponent(const APawn* Pawn)
{
	if (AAIController* AIController { Pawn->GetController<AAIController>() })
	{
		return AIController->GetBlackboardComponent();
	}

	return nullptr;
}

UMusicPlayerSubsystem* UGameStatics::GetMusicSubsystem(const AActor* ContextActor)
{
	const UGameInstance* GameInstance { ContextActor->GetGameInstance() };
	UMusicPlayerSubsystem* MusicPlayerSubsystem { GameInstance->GetSubsystem<UMusicPlayerSubsystem>() };
	check(MusicPlayerSubsystem);
	return MusicPlayerSubsystem;
}

APlayerCharacter* UGameStatics::GetPlayer(const AActor* ContextActor)
{
	const APlayerController* PlayerController { UGameplayStatics::GetPlayerController(ContextActor, 0) };
	check(PlayerController);
	APlayerCharacter* PlayerCharacter { PlayerController->GetPawn<APlayerCharacter>() };
	return PlayerCharacter;
}
