//
// GamePlayerController.cpp
// Implementation of the AGamePlayerController class.
//

#include "FrozenDread/Player/GamePlayerController.h"

#include "FrozenDread/Gameplay/InteractionComponent.h"
#include "FrozenDread/Player/GamePlayerState.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/UI/GameHUD.h"

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Cache references
	PlayerCharacter = CastChecked<APlayerCharacter>(GetCharacter());
	GamePlayerState = GetPlayerState<AGamePlayerState>();

	// Setup HUD
	AGameHUD* GameHUD { GetHUD<AGameHUD>() };
	check(GameHUD);
	GameHUD->InitAndAddToViewport();

	// Setup InteractionComponent on the player character
	PlayerCharacter->GetInteractionComponent()->SetInteractionWidget(GameHUD->GetInteractionWidget());

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
IsWearingSuitCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("game.debug.player.is_wearing_suit"));
#endif
}

void AGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	if (GamePlayerState.IsValid())
	{
		if (IsWearingSuitCVar->GetInt() == 1)
		{
			SwitchPlayerSuit();
		}
	}
#endif
}

void AGamePlayerController::SwitchPlayerSuit() const
{
	check(PlayerCharacter.IsValid() && GamePlayerState.IsValid());
	
	PlayerCharacter->SwitchToExoSuit();
	GamePlayerState->SetIsWearingSuit(true);
}
