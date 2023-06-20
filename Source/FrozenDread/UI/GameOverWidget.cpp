//
// GameOverWidget.cpp
// Implementation of the UGameOverWidget class.
//

#include "FrozenDread/UI/GameOverWidget.h"

#include "Components/Button.h"

#include "FrozenDread/System/GameEventSubsystem.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Set the button events
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UGameOverWidget::QuitButtonClicked);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::RestartButtonClicked);
	}
}

void UGameOverWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(Animation);
}

void UGameOverWidget::QuitButtonClicked()
{
	const UGameEventSubsystem* EventSubsystem { GetWorld()->GetSubsystem<UGameEventSubsystem>() };
	check(EventSubsystem);
	EventSubsystem->PlayerRequestedLevelQuit();
}

void UGameOverWidget::RestartButtonClicked()
{
	const UGameEventSubsystem* EventSubsystem { GetWorld()->GetSubsystem<UGameEventSubsystem>() };
	check(EventSubsystem);
	EventSubsystem->PlayerRequestedRestart();
}
