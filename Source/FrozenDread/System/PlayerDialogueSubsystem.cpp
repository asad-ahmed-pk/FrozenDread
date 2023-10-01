//
// PlayerDialogueSubsystem.cpp
// Implementation of the UPlayerDialogueSubsystem class.
//

#include "FrozenDread/System/PlayerDialogueSubsystem.h"

#include "FrozenDread/UI/DialogueWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Kismet/KismetStringLibrary.h"

const FString MAIN_MENU_LEVEL_NAME { "MainMenu" };

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
			if (const FString LevelName = World->GetMapName(); LevelName.Equals(MAIN_MENU_LEVEL_NAME))
			{
				return false;
			}
		}
	}
    
	return true;
}

void UPlayerDialogueSubsystem::Setup(UDialogueWidget* DialogueWidgetPtr, AGamePlayerController* LocalPlayerController)
{
	PlayerController = LocalPlayerController;
	
	DialogueWidget = DialogueWidgetPtr;
	DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);
	DialogueWidget->GetNextEventRef().AddLambda([this]()
	{
		NextDialogueItemRequested();
	});

	// Play any dialogue if the queue is not empty
	if (!DialogueQueue.IsEmpty())
	{
		BeginDialogueMode();
	}
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
			UpdateUI();
		}
	}
}

void UPlayerDialogueSubsystem::AddDialogueItem(const FDialogueItem& DialogueItem, const TOptional<const FDialogueCallBack>& CallBackRef)
{
	DialogueQueue.Enqueue(DialogueItem);
	if (!DialogueQueue.IsEmpty() && DialogueWidget != nullptr)
	{
		CallBack = CallBackRef;
		BeginDialogueMode();
	}
}

// Move the game into dialogue mode
void UPlayerDialogueSubsystem::BeginDialogueMode()
{
	// Set flag so that this sub-system can begin ticking
	IsCurrentlyPlaying = true;

	// Display dialogue widget
	if (!DialogueWidget->IsVisible())
	{
		DialogueWidget->SetVisibility(ESlateVisibility::Visible);
	}

	// Enable UI input
	const FInputModeUIOnly UIInput;
	GetWorld()->GetFirstPlayerController()->SetInputMode(UIInput);

	// Set mouse onto the dialogue widget
	if (PlayerController.IsValid())
	{
		PlayerController->SetMousePointerOnCenter();
	}

	// Pause the game if not already paused so player can focus on dialogue
	if (!UGameplayStatics::IsGamePaused(this))
	{
		UGameplayStatics::SetGamePaused(this, true);
	}
}

// Exit the dialogue mode and go back to game mode
void UPlayerDialogueSubsystem::EndDialogueMode()
{
	// Hide dialogue
	DialogueWidget->SetText(TEXT(""));
	DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);

	// Set back UI mode to game
	const FInputModeGameOnly GameInput;
	GetWorld()->GetFirstPlayerController()->SetInputMode(GameInput);

	// Unpause game
	if (UGameplayStatics::IsGamePaused(this))
	{
		UGameplayStatics::SetGamePaused(this, false);
	}

	// Call the callback function to notify that the dialog finished playing
	// ReSharper disable once CppExpressionWithoutSideEffects
	if (CallBack.IsSet())
	{
		CallBack->ExecuteIfBound();
	}
}

// Update the UI to show the next text character
void UPlayerDialogueSubsystem::UpdateUI()
{
	check(!DialogueQueue.IsEmpty());
	check(DialogueWidget);

	static int32 CurrentTextLength { 0 };

	// Get the new updated text to display
	const FString TextToPlay { DialogueQueue.Peek()->DialogueText.ToString() };
	CurrentTextLength += 1;

	// Increase text size by 1 and display
	const FString DisplayText { UKismetStringLibrary::GetSubstring(TextToPlay, 0, CurrentTextLength) };
	DialogueWidget->SetText(DisplayText);

	// Text is complete
	if (CurrentTextLength == TextToPlay.Len())
	{
		DialogueWidget->SetToNextMode();
		DialogueQueue.Dequeue(LastPlayedItem);
		CurrentTextLength = 0;
		IsCurrentlyPlaying = false;
	}
}

void UPlayerDialogueSubsystem::NextDialogueItemRequested()
{
	// If we have an item in the queue, process that
	if (!DialogueQueue.IsEmpty())
	{
		IsCurrentlyPlaying = true;
	}
	else
	{
		EndDialogueMode();
	}
}
