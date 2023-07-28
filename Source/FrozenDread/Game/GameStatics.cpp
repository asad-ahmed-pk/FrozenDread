//
// GameStatics.cpp
// Implementation of the UGameStatics class.
//

#include "FrozenDread/Game/GameStatics.h"

#include "AIController.h"
#include "FrozenDread/Gameplay/GameLevelScriptActor.h"
#include "FrozenDread/System/MusicPlayerSubsystem.h"

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
