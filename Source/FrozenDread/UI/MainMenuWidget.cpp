//
// MainMenuWidget.cpp
// Implementation of the UMainMenuWidget class.
//


#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "FrozenDread/Game/BaseGameInstance.h"
#include "FrozenDread/System/GameUISubsystem.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::StartGameButtonPressed);
	}
	
	if (EndGameButton)
	{
		EndGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::EndGameButtonPressed);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OptionsButtonPressed);
	}

	if (CreditsButton)
	{
		CreditsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::CreditsButtonPressed);
	}
}

void UMainMenuWidget::StartGameButtonPressed()
{
	const UBaseGameInstance* GameInstance { CastChecked<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this)) };
	GameInstance->StartGameRequested();
}

void UMainMenuWidget::EndGameButtonPressed()
{
	const UBaseGameInstance* GameInstance { CastChecked<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this)) };
	GameInstance->QuitGameRequested();
}

void UMainMenuWidget::OptionsButtonPressed()
{
	const UBaseGameInstance* GameInstance { CastChecked<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this)) };
	UGameUISubsystem* GameUISubsystem { GameInstance->GetSubsystem<UGameUISubsystem>() };
	GameUISubsystem->ShowGameOptions();
}

void UMainMenuWidget::CreditsButtonPressed()
{
	const UBaseGameInstance* GameInstance { CastChecked<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this)) };
	UGameUISubsystem* GameUISubsystem { GameInstance->GetSubsystem<UGameUISubsystem>() };
	GameUISubsystem->ShowCredits();
}
