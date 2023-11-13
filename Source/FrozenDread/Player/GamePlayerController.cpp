//
// GamePlayerController.cpp
// Implementation of the AGamePlayerController class.
//

#include "FrozenDread/Player/GamePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FrozenDread/Game/PlayGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "FrozenDread/Gameplay/InteractionComponent.h"
#include "FrozenDread/Player/GamePlayerState.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/Player/Inventory.h"
#include "FrozenDread/UI/GameHUD.h"
#include "FrozenDread/UI/InventoryWidget.h"
#include "FrozenDread/System/PlayerDialogueSubsystem.h"
#include "FrozenDread/System/GameObjectiveSubsystem.h"
#include "FrozenDread/UI/CinematicWidget.h"
#include "FrozenDread/UI/PauseMenuWidget.h"

AGamePlayerController::AGamePlayerController() : Inventory(CreateDefaultSubobject<UInventory>(TEXT("Inventory")))
{
	
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Cache references
	PlayerCharacter = CastChecked<APlayerCharacter>(GetCharacter());
	GamePlayerState = GetPlayerState<AGamePlayerState>();

	// Setup HUD
	GameHUD = GetHUD<AGameHUD>();
	check(GameHUD.IsValid());
	GameHUD->InitAndAddToViewport();

	// Bind events for UI
	const UInventoryWidget* InventoryWidget = GameHUD->GetInventoryWidget();
	check(InventoryWidget);
	check(Inventory);
	InventoryWidget->SubscribeToEvent(Inventory->GetInventoryItemAddedEvent());

	// Setup enhanced input
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		check(MappingContext);
		Subsystem->AddMappingContext(MappingContext, 1);
	}

	// Setup InteractionComponent on the player character
	PlayerCharacter->GetInteractionComponent()->SetInteractionWidget(GameHUD->GetInteractionWidget());

	// Setup dialogue subsystem
	UPlayerDialogueSubsystem* DialogueSubsystem { GetWorld()->GetSubsystem<UPlayerDialogueSubsystem>() };
	DialogueSubsystem->Setup(GameHUD->GetDialogueWidget(), this);

	// Setup objectives subsystem
	UGameObjectiveSubsystem* GameObjectiveSubsystem { GetWorld()->GetSubsystem<UGameObjectiveSubsystem>() };
	GameObjectiveSubsystem->Setup(GameHUD->GetObjectiveWidget());

	// Play intro widget animation
	PlayIntro();
}

void AGamePlayerController::SetMousePointerOnCenter()
{
	FViewport* Viewport { GetLocalPlayer()->ViewportClient->Viewport };
	if (Viewport)
	{
		const FIntPoint ViewportSize {Viewport->GetSizeXY() };
		Viewport->SetMouse(ViewportSize.X / 2, ViewportSize.Y / 2);
	} 
}

void AGamePlayerController::SetMainMenuIsActive(bool IsActive)
{
	// Set input mode
	if (IsActive)
	{
		SetInputMode(FInputModeUIOnly{});
		SetShowMouseCursor(true);
	}
	else
	{
		SetInputMode(FInputModeGameOnly{});
		SetShowMouseCursor(false);
	}

	// Show or hide pause menu
	check(GameHUD.IsValid());
	GameHUD->GetPauseMenuWidget()->SetVisibility(IsActive ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);

	// Pause / unpause game
	UGameplayStatics::SetGamePaused(this, IsActive);
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Inventory toggle action
		check(InventoryToggleAction);
		EnhancedInputComponent->BindAction(InventoryToggleAction, ETriggerEvent::Triggered, this, &AGamePlayerController::ToggleInventory);
	}
}

void AGamePlayerController::ToggleInventory()
{
	check(GameHUD.IsValid());

	IsViewingInventory = !IsViewingInventory;
	GameHUD->SetInventoryWidgetVisible(IsViewingInventory);

	// Disable input for the character if showing inventory
	if (IsViewingInventory)
	{
		PlayerCharacter->DisableInput(this);
		const FInputModeGameAndUI InputMode;
		SetInputMode(InputMode);
	}
	else
	{
		PlayerCharacter->EnableInput(this);
		const FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
	}

	// Mouse pointer
	bShowMouseCursor = IsViewingInventory;
	bEnableClickEvents = IsViewingInventory;
	bEnableMouseOverEvents = IsViewingInventory;

	// Play inventory toggle sound
	check(InventoryToggleSound);
	UGameplayStatics::PlaySound2D(this, InventoryToggleSound);
}

void AGamePlayerController::PlayIntro()
{
	check(GameHUD.IsValid());
	UCinematicWidget* CinematicWidget { GameHUD->GetCinematicWidget() };

	// Show the widget
	CinematicWidget->SetVisibility(ESlateVisibility::Visible);

	// Disable input
	check(PlayerCharacter.IsValid());
	PlayerCharacter->DisableInput(this);

	// Play intro fade in animation on UI
	CinematicWidget->PlayFadeInAnimation([&]()
	{
		// Enable input again
		PlayerCharacter->EnableInput(this);

		// Notify level coordinator that intro completed
		const APlayGameMode* GameMode { CastChecked<APlayGameMode>(UGameplayStatics::GetGameMode(this)) };
		GameMode->GetLevelCoordinator()->PlayerIntroSequenceCompleted();
	});
}