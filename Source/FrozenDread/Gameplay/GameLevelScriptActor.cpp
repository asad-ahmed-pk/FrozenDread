//
// GameLevelScriptActor.cpp
// Implementation of the AGameLevelScriptActor class.
//

#include "FrozenDread/Gameplay/GameLevelScriptActor.h"
#include "FrozenDread/Game/Dialogue.h"

void AGameLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
}

void AGameLevelScriptActor::PlayerDialogueFinishedPlaying_Implementation(const FDialogueItem& DialogueItem)
{
	UE_LOG(LogTemp, Warning, TEXT("Implement PlayerDialogueFinishedPlaying() in BP"));
}

void AGameLevelScriptActor::PlayerTriedLockedDoor_Implementation(ADoor* Door)
{
	UE_LOG(LogTemp, Warning, TEXT("Implement PlayerTriedLockedDoor() in BP"));
}

void AGameLevelScriptActor::PlayerInteractedWithItem_Implementation(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Implement PlayerInteractedWithItem() in BP"));
}

void AGameLevelScriptActor::PlayerWasCaught_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Implement PlayerWasCaught() in BP"));
}
