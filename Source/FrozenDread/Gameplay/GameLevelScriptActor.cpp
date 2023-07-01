//
// GameLevelScriptActor.cpp
// Implementation of the AGameLevelScriptActor class.
//

#include "FrozenDread/Gameplay/GameLevelScriptActor.h"

void AGameLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
}

void AGameLevelScriptActor::PlayerWasCaught_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Implement PlayerWasCaught() in BP"));
}
