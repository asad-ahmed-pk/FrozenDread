//
// PauseMenu.cpp
// Implementation of the UPauseMenu class.
//


#include "FrozenDread/UI/PauseMenuWidget.h"

#include "Components/Button.h"
#include "FrozenDread/Player/GamePlayerController.h"
#include "FrozenDread/System/GameUISubsystem.h"

#include "Kismet/GameplayStatics.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OptionsButtonClicked);
	}

	if (ExitToMenuButton)
	{
		ExitToMenuButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::ExitButtonClicked);
	}

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::ResumeButtonClicked);
	}
}

void UPauseMenuWidget::OptionsButtonClicked()
{
	const UGameInstance* GameInstance { UGameplayStatics::GetGameInstance(this) };
	UGameUISubsystem* UISubsystem { GameInstance->GetSubsystem<UGameUISubsystem>() };
	
	check(UISubsystem);

	UISubsystem->ShowGameOptions();
}

void UPauseMenuWidget::ExitButtonClicked()
{
	// TODO: Show confirmation dialogue and exit
}

void UPauseMenuWidget::ResumeButtonClicked()
{
	AGamePlayerController* PlayerController { GetOwningPlayer<AGamePlayerController>() };
	check(PlayerController);
	PlayerController->SetMainMenuIsActive(false);
}
