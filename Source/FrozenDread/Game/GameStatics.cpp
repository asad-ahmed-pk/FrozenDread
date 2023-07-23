//
// GameStatics.cpp
// Implementation of the UGameStatics class.
//

#include "FrozenDread/Game/GameStatics.h"

#include "AIController.h"
#include "FrozenDread/Gameplay/GameLevelScriptActor.h"

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
