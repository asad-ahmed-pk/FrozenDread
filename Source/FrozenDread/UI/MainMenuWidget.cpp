//
// MainMenuWidget.cpp
// Implementation of the UMainMenuWidget class.
//


#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "FrozenDread/Game/BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"

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
}

void UMainMenuWidget::StartGameButtonPressed()
{
	const UBaseGameInstance* GameInstance { CastChecked<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this)) };
	GameInstance->StartGameRequested();
}

void UMainMenuWidget::EndGameButtonPressed()
{
	UBaseGameInstance::QuitGameRequested();
}

void UMainMenuWidget::OptionsButtonPressed()
{
	const UBaseGameInstance* GameInstance { CastChecked<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this)) };
	GameInstance->OptionsMenuRequested();
}
