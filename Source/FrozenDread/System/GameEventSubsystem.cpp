//
// GameEventSubsystem.cpp
// Implementation of the UGameEventSubsystem class.
//

#include "FrozenDread/System/GameEventSubsystem.h"

#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/Player/GamePlayerController.h"

void UGameEventSubsystem::PlayerInteractedWithExoSuit(const APlayerCharacter* PlayerCharacter)
{
	check(PlayerCharacter);

	const AGamePlayerController* PlayerController { PlayerCharacter->GetController<AGamePlayerController>() };
	check(PlayerController);

	PlayerController->SwitchPlayerSuit();

	PlayerIsWearingExoSuit = true;
}