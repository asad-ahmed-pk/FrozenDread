//
// GameUISubsystem.cpp
// Implementation of the UGameUISubsystem class.
//

#include "GameUISubsystem.h"

#include "Blueprint/UserWidget.h"
#include "FrozenDread/UI/KeyBindsWidget.h"
#include "FrozenDread/UI/OptionsMenuWidget.h"

constexpr int32 VIEW_PORT_ORDER_OPTIONS_MENU { 10 };
constexpr int32 VIEW_PORT_ORDER_KEYBINDS_MENU { 11 };
constexpr int32 VIEW_PORT_ORDER_LOADING_SCREEN { 20 };

void UGameUISubsystem::Init(const FGameWidgetClass& WidgetClasses)
{
	// Subscribe to level loading events
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UGameUISubsystem::OnMapPostLoad);

	// Create game widgets
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
		OptionsWidget->OnBackButtonClicked.AddUObject(this, &UGameUISubsystem::NavigateBack);
	}

	// Keybinds widget
	if (WidgetClass.KeyBindsWidgetClass)
	{
		KeyBindsWidget = CreateWidgetOfClass<UKeyBindsWidget>(WidgetClass.KeyBindsWidgetClass, VIEW_PORT_ORDER_KEYBINDS_MENU);
		KeyBindsWidget->OnCloseButtonClicked.AddUObject(this, &UGameUISubsystem::NavigateBack);
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

void UGameUISubsystem::OnMapPostLoad(UWorld* World)
{
	// Hide loading screen
	HideLoadingScreen();
}

void UGameUISubsystem::ShowKeyBindsWidget()
{
	check(KeyBindsWidget.IsValid());
	PushWidgetOntoStack(KeyBindsWidget);
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
