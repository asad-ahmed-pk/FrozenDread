//
// PlayerDialogueSubsystem.cpp
// Implementation of the UPlayerDialogueSubsystem class.
//

#include "FrozenDread/System/PlayerDialogueSubsystem.h"

#include "FrozenDread/UI/DialogueWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Kismet/KismetStringLibrary.h"

const FString GMain_Menu_Level_Name { "MainMenu" };

// Settings for this subsystem
constexpr float TEXT_TYPING_INTERVAL { 0.02F };

bool UPlayerDialogueSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// Do not create if this is the main menu map
	// Check if the level is the main menu level
	if (GEngine && GEngine->GetWorldFromContextObject(Outer, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObject(Outer, EGetWorldErrorMode::LogAndReturnNull))
		{
			if (const FString LevelName = World->GetMapName(); LevelName.Equals(GMain_Menu_Level_Name))
			{
				return false;
			}
		}
	}
    
	return true;
}

void UPlayerDialogueSubsystem::Setup(UDialogueWidget* DialogueWidgetPtr)
{
	DialogueWidget = DialogueWidgetPtr;
	DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);
	DialogueWidget->GetNextEventRef().AddLambda([this]()
	{
		NextDialogueItemRequested();
	});

	// Play any dialogue if it queue is not empty
	if (!DialogueQueue.IsEmpty())
	{
		PlayNextDialogueText();
	}
}

void UPlayerDialogueSubsystem::AddDialogueItem(const FDialogueItem& DialogueItem, const FDialogueCallBack& CallBackRef)
{
	DialogueQueue.Enqueue(DialogueItem);
	if (!DialogueQueue.IsEmpty() && DialogueWidget != nullptr)
	{
		CallBack = CallBackRef;
		PlayNextDialogueText();
	}
}

bool UPlayerDialogueSubsystem::IsTickableWhenPaused() const
{
	return true;
}

TStatId UPlayerDialogueSubsystem::GetStatId() const
{
	return TStatId();
}

void UPlayerDialogueSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	static float AccumulatedTime { 0.0F };

	if (IsCurrentlyPlaying)
	{
		AccumulatedTime += DeltaTime;
		if (AccumulatedTime >= TEXT_TYPING_INTERVAL) {
			AccumulatedTime = 0.0F;
			TextTypeTimer();
		}
	}
}

void UPlayerDialogueSubsystem::PlayNextDialogueText()
{
	// Reset the length to 0
	CurrentTextLength = 0;
	
	// Set the flag for text typing and show dialogue widget
	if (!DialogueWidget->IsVisible())
	{
		DialogueWidget->SetVisibility(ESlateVisibility::Visible);
	}

	IsCurrentlyPlaying = true;
}

void UPlayerDialogueSubsystem::TextTypeTimer()
{
	check(!DialogueQueue.IsEmpty());
	check(DialogueWidget);

	// Get the new updated text to display
	const FString TextToPlay { DialogueQueue.Peek()->DialogueText.ToString() };
	CurrentTextLength += 1;

	// Increase text size by 1 and display
	const FString DisplayText { UKismetStringLibrary::GetSubstring(TextToPlay, 0, CurrentTextLength) };
	DialogueWidget->SetText(DisplayText);

	// TODO: Figure out if this is possible. Pausing the game currently stops this subsystem's timer :(
	// Pause the game if not already paused so player can focus on dialogue
	if (!UGameplayStatics::IsGamePaused(this))
	{
		UGameplayStatics::SetGamePaused(this, true);
	}

	// If all text is complete, show the "next" icon and wait for player input
	if (CurrentTextLength == TextToPlay.Len())
	{
		DialogueWidget->SetToNextMode();

		DialogueQueue.Dequeue(LastPlayedItem);

		IsCurrentlyPlaying = false;

		// Enable UI input
		const FInputModeUIOnly UIInput;
		GetWorld()->GetFirstPlayerController()->SetInputMode(UIInput);
	}
}

void UPlayerDialogueSubsystem::NextDialogueItemRequested()
{
	// If we have an item in the queue, process that
	if (!DialogueQueue.IsEmpty())
	{
		PlayNextDialogueText();
	}
	else
	{
		// Hide dialogue
		DialogueWidget->SetText(TEXT(""));
		DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);

		// Unpause game
		if (UGameplayStatics::IsGamePaused(this))
		{
			UGameplayStatics::SetGamePaused(this, false);
		}

		// Set back UI mode to game
		const FInputModeGameOnly GameInput;
		GetWorld()->GetFirstPlayerController()->SetInputMode(GameInput);

		// Call the callback function to notify that the dialog finished playing
		// ReSharper disable once CppExpressionWithoutSideEffects
		if (CallBack.IsSet())
		{
			CallBack->ExecuteIfBound();
		}
	}
}
