//
// GameUISubsystem.cpp
// Implementation of the UGameUISubsystem class.
//

#include "GameUISubsystem.h"

#include "Blueprint/UserWidget.h"
#include "FrozenDread/UI/ConfirmationDialogWidget.h"
#include "FrozenDread/UI/CreditsWidget.h"
#include "FrozenDread/UI/GameSettingsWidget.h"
#include "FrozenDread/UI/KeyBindsWidget.h"
#include "FrozenDread/UI/OptionsMenuWidget.h"

constexpr int32 VIEW_PORT_ORDER_OPTIONS_MENU { 10 };
constexpr int32 VIEW_PORT_ORDER_KEYBINDS_MENU { 11 };
constexpr int32 VIEW_PORT_ORDER_SETTINGS_SCREEN { 12 };
constexpr int32 VIEW_PORT_ORDER_CREDITS_SCREEN { 13 };
constexpr int32 VIEW_PORT_ORDER_CONFIRMATION_DIALOG { 14 };
constexpr int32 VIEW_PORT_ORDER_LOADING_SCREEN { 20 };

void UGameUISubsystem::Init(const FGameWidgetClass& WidgetClasses)
{
	// Subscribe to level loading events
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UGameUISubsystem::OnMapPostLoad);

	// Create game widgets
	GameWidgetClasses = WidgetClasses;
	CreateWidgets(WidgetClasses);
}

void UGameUISubsystem::CreateWidgets(const FGameWidgetClass& WidgetClass)
{
	// Loading screen widget
	if (WidgetClass.LoadingScreenWidget)
	{
		LoadingScreenWidget = CreateWidgetOfClass<UUserWidget>(WidgetClass.LoadingScreenWidget, VIEW_PORT_ORDER_LOADING_SCREEN);
	}
	
	// Game options widget
	if (WidgetClass.GameOptionsWidgetClass)
	{
		OptionsWidget = CreateWidgetOfClass<UOptionsMenuWidget>(WidgetClass.GameOptionsWidgetClass, VIEW_PORT_ORDER_OPTIONS_MENU);
		OptionsWidget->OnKeyBindButtonClicked.AddUObject(this, &UGameUISubsystem::ShowKeyBindsWidget);
		OptionsWidget->OnSettingsButtonClicked.AddUObject(this, &UGameUISubsystem::ShowSettingsWidget);
		OptionsWidget->OnBackButtonClicked.AddUObject(this, &UGameUISubsystem::NavigateBack);
	}

	// Keybinds widget
	if (WidgetClass.KeyBindsWidgetClass)
	{
		KeyBindsWidget = CreateWidgetOfClass<UKeyBindsWidget>(WidgetClass.KeyBindsWidgetClass, VIEW_PORT_ORDER_KEYBINDS_MENU);
		KeyBindsWidget->OnCloseButtonClicked.AddUObject(this, &UGameUISubsystem::NavigateBack);
	}

	// Game settings widget
	if (WidgetClass.GameSettingsWidgetClass)
	{
		GameSettingsWidget = CreateWidgetOfClass<UGameSettingsWidget>(WidgetClass.GameSettingsWidgetClass, VIEW_PORT_ORDER_SETTINGS_SCREEN);
		GameSettingsWidget->OnBackButtonClicked.AddUObject(this, &UGameUISubsystem::NavigateBack);
	}

	// Credits widget
	if (WidgetClass.CreditsWidgetClass)
	{
		CreditsWidget = CreateWidgetOfClass<UCreditsWidget>(WidgetClass.CreditsWidgetClass, VIEW_PORT_ORDER_CREDITS_SCREEN);
		CreditsWidget->OnBackButtonClicked.AddUObject(this, &UGameUISubsystem::NavigateBack);
	}

	// Confirmation dialog widget
	if (WidgetClass.ConfirmationDialogWidgetClass)
	{
		ConfirmationDialogWidget = CreateWidgetOfClass<UConfirmationDialogWidget>(WidgetClass.ConfirmationDialogWidgetClass, VIEW_PORT_ORDER_CONFIRMATION_DIALOG);
	}
}

void UGameUISubsystem::ShowLoadingScreen(const TFunction<void()>& CompletionCallBack)
{
	constexpr float DELAY_SECONDS { 2.0F };
	
	if (LoadingScreenWidget.IsValid())
	{
		LoadingScreenWidget->AddToViewport(10);
		LoadingScreenWidget->SetVisibility(ESlateVisibility::Visible);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&, CompletionCallBack]
		{
			IsLoadingScreenActive = true;
			CompletionCallBack();
		}), DELAY_SECONDS, false);
	}
}

void UGameUISubsystem::HideLoadingScreen()
{
	if (LoadingScreenWidget.IsValid())
	{
		LoadingScreenWidget->RemoveFromParent();
		IsLoadingScreenActive = false;
	}
}

void UGameUISubsystem::ShowGameOptions()
{
	check(OptionsWidget.IsValid());
	PushWidgetOntoStack(OptionsWidget);
}

void UGameUISubsystem::ShowCredits()
{
	check(CreditsWidget.IsValid());
	PushWidgetOntoStack(CreditsWidget);
}

void UGameUISubsystem::ShowConfirmationDialog(EConfirmationDialogType Type, TFunction<void(bool)> CallBack)
{
	check(ConfirmationDialogWidget.IsValid());

	FText TitleText { FText::FromString("") };
	FText MessageText { FText::FromString("") };

	switch (Type)
	{
	case EConfirmationDialogType::QUIT_GAME:
		TitleText = FText::FromString("Quit Game");
		MessageText = FText::FromString("Are you sure you want to quit?");
		break;

	case EConfirmationDialogType::RETURN_TO_MENU:
		TitleText = FText::FromString("Return to Main Menu");
		MessageText = FText::FromString("Are you sure you want to return to the main menu?");
		break;
	}

	ConfirmationDialogWidget->SetContent(TitleText, MessageText);
	
	PushWidgetOntoStack(ConfirmationDialogWidget);
	ConfirmationDialogWidget->OnConfirmationResultSelected.BindLambda([&, CallBack](bool IsConfirmed){
		NavigateBack();
		CallBack(IsConfirmed);
	});
}

void UGameUISubsystem::OnMapPostLoad(UWorld* World)
{
	// Hide loading screen
	HideLoadingScreen();

	// Re-create widgets since new map was loaded
	CreateWidgets(GameWidgetClasses);
}

void UGameUISubsystem::ShowKeyBindsWidget()
{
	check(KeyBindsWidget.IsValid());
	PushWidgetOntoStack(KeyBindsWidget);
}

void UGameUISubsystem::ShowSettingsWidget()
{
	check(GameSettingsWidget.IsValid());
	PushWidgetOntoStack(GameSettingsWidget);
}

void UGameUISubsystem::PushWidgetOntoStack(const TWeakObjectPtr<UUserWidget>& Widget)
{
	if (!NavigationStack.IsEmpty())
	{
		// Hide the bottom widget
		NavigationStack[NavigationStack.Num() - 1]->SetVisibility(ESlateVisibility::Collapsed);
	}

	Widget->SetVisibility(ESlateVisibility::Visible);
	NavigationStack.Add(Widget);
}

void UGameUISubsystem::NavigateBack()
{
	if (!NavigationStack.IsEmpty())
	{
		const int32 TopIndex { NavigationStack.Num() - 1 };

		const TWeakObjectPtr<UUserWidget> TopWidget { NavigationStack[TopIndex] };
		NavigationStack.RemoveAt(TopIndex);

		TopWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (!NavigationStack.IsEmpty())
	{
		NavigationStack[NavigationStack.Num() - 1]->SetVisibility(ESlateVisibility::Visible);
	}
}
