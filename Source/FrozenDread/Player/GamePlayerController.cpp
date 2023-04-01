//
// GamePlayerController.cpp
// Implementation of the AGamePlayerController class.
//

#include "FrozenDread/Player/GamePlayerController.h"

#include "GamePlayerState.h"
#include "FrozenDread/Player/PlayerCharacter.h"

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = CastChecked<APlayerCharacter>(GetCharacter());
	GamePlayerState = GetPlayerState<AGamePlayerState>();
}

void AGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	if (GamePlayerState.IsValid())
	{
		const IConsoleVariable* CVar { IConsoleManager::Get().FindConsoleVariable(TEXT("game.debug.player.is_wearing_suit")) };
		if (const bool IsWearingCVar { CVar->GetInt() == 1 })
		{
			SwitchPlayerSuit();
		}
	}
#endif
	
}

void AGamePlayerController::SwitchPlayerSuit()
{
	check(PlayerCharacter.IsValid());
	PlayerCharacter->SwitchToExoSuit();
}
