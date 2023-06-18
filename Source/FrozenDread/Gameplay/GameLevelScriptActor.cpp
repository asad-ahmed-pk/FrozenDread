//
// GameLevelScriptActor.cpp
// Implementation of the AGameLevelScriptActor class.
//

#include "FrozenDread/Gameplay/GameLevelScriptActor.h"

#include "FrozenDread/Player/GamePlayerController.h"
#include "FrozenDread/UI/GameHUD.h"
#include "FrozenDread/System/PlayerDialogueSubsystem.h"

void AGameLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
}

void AGameLevelScriptActor::PlayerWasCaught_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Implement PlayerWasCaught() in BP"));
}
