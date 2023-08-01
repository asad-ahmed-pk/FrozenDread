//
// GameEventSubsystem.cpp
// Implementation of the UGameEventSubsystem class.
//

#include "FrozenDread/System/GameEventSubsystem.h"

#include "FrozenDread/System/MusicPlayerSubsystem.h"
#include "FrozenDread/Game/GameStatics.h"
#include "FrozenDread/Gameplay/GameLevelScriptActor.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/UI/GameHUD.h"
#include "FrozenDread/UI/GameOverWidget.h"

#include "Kismet/GameplayStatics.h"

void UGameEventSubsystem::Setup(APlayerCharacter* PlayerCharacter)
{
	Player = PlayerCharacter;
}

void UGameEventSubsystem::PlayerWasCaught() const
{
	// Destroy monsters
	for (auto Monster : Monsters)
	{
		if (Monster.IsValid())
		{
			Monster->Destroy();
		}
	}

	// Disable player input
	check(Player.IsValid());
	APlayerController* PlayerController { CastChecked<APlayerController>(Player->GetController()) };
	Player->DisableInput(PlayerController);

	// Stop all music
	UGameStatics::GetMusicSubsystem(Player.Get())->Stop();
	
	// Notify level script actor that the player was caught
	AGameLevelScriptActor* LevelScript { CastChecked<AGameLevelScriptActor>(GetWorld()->GetLevelScriptActor()) };
	LevelScript->PlayerWasCaught();
}

void UGameEventSubsystem::PlayerRequestedRestart() const
{
	// Set the input mode back to gameplay
	const FInputModeGameOnly InputMode;
	Player->GetController<APlayerController>()->SetInputMode(InputMode);
	Player->GetController<APlayerController>()->SetShowMouseCursor(false);
	
	// TODO: Use a checkpoint system to load the level
	const FName CurrentLevelName { UGameplayStatics::GetCurrentLevelName(this) };
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}

void UGameEventSubsystem::PlayerRequestedLevelQuit() const
{
	// TODO: Go back to the main menu once main menu is implemented
	check(Player.IsValid());
	UKismetSystemLibrary::QuitGame(this, Player->GetController<APlayerController>(), EQuitPreference::Quit, false);
}

void UGameEventSubsystem::PlayerIsBeingChased(bool IsChased)
{
	if (IsChased != IsMonsterChasingPlayer)
	{
		IsMonsterChasingPlayer = IsChased;
		OnPlayerBeingChased.Broadcast(IsChased);
	}
}

void UGameEventSubsystem::DeathLevelSequenceFinished()
{
	check(Player.IsValid());

	// Show the game over widget
	const AGameHUD* GameHUD { Player->GetController<APlayerController>()->GetHUD<AGameHUD>() };
	UGameOverWidget* GameOverWidget { GameHUD->GetGameOverWidget() };
	GameOverWidget->Show();

	// Enable UI input only
	const FInputModeUIOnly InputMode;
	Player->GetController<APlayerController>()->SetInputMode(InputMode);
	Player->GetController<APlayerController>()->SetShowMouseCursor(true);
}

void UGameEventSubsystem::SetPlayerInputEnabled(bool IsEnabled)
{
	check(Player.IsValid());
	APlayerController* PlayerController { Player->GetController<APlayerController>() };

	if (IsEnabled)
	{
		Player->EnableInput(PlayerController);
	}
	else
	{
		Player->DisableInput(PlayerController);
	}
}

void UGameEventSubsystem::SpawnMonster(TSubclassOf<AMonster> MonsterClass, const FVector& Location)
{
	AMonster* Monster { GetWorld()->SpawnActor<AMonster>(MonsterClass, Location, FRotator::ZeroRotator) };
	Monster->Init();
	Monsters.Add(Monster);
}
