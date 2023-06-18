//
// GameEventSubsystem.cpp
// Implementation of the UGameEventSubsystem class.
//

#include "FrozenDread/System/GameEventSubsystem.h"

#include "FrozenDread/Gameplay/GameLevelScriptActor.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/Player/GamePlayerController.h"

void UGameEventSubsystem::Setup(APlayerCharacter* PlayerCharacter, AMonster* MonsterCharacter)
{
	Player = PlayerCharacter;
	Monster = MonsterCharacter;
}

void UGameEventSubsystem::PlayerInteractedWithExoSuit(const APlayerCharacter* PlayerCharacter)
{
	check(PlayerCharacter);

	const AGamePlayerController* PlayerController { PlayerCharacter->GetController<AGamePlayerController>() };
	check(PlayerController);

	PlayerController->SwitchPlayerSuit();

	PlayerIsWearingExoSuit = true;
}

void UGameEventSubsystem::PlayerWasCaught() const
{
	// Disable monster
	check(Monster.IsValid());
	Monster->Destroy();

	// Disable player input
	check(Player.IsValid());
	APlayerController* PlayerController { CastChecked<APlayerController>(Player->GetController()) };
	Player->DisableInput(PlayerController);
	
	// Notify level script actor that the player was caught
	AGameLevelScriptActor* LevelScript { CastChecked<AGameLevelScriptActor>(GetWorld()->GetLevelScriptActor()) };
	LevelScript->PlayerWasCaught();
}
