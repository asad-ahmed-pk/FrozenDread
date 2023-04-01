//
// PlayGameMode.cpp
// Implementation of the APlayGameMode class.
//


#include "FrozenDread/Game/PlayGameMode.h"

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
