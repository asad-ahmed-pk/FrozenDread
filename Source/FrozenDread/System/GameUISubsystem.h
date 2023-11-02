//
// GameUISubsystem.h
// Definition of the UGameUISubsystem class.
//

#pragma once

#include <type_traits>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FrozenDread/Game/MainUserInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "GameUISubsystem.generated.h"

class UGameSettingsWidget;
class UKeyBindsWidget;
class UOptionsMenuWidget;

/**
 * Subsystem responsible for the main game UI (main menu, options screen, etc...) and NOT the in-game player UI (HUD).
 */
UCLASS()
class FROZENDREAD_API UGameUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Init this subsystem */
	void Init(const FGameWidgetClass& WidgetClasses);

	/** Create all needed widgets */
	void CreateWidgets(const FGameWidgetClass& WidgetClass);

	/** Show the loading screen and call the callback */
	void ShowLoadingScreen(const TFunction<void()>& CompletionCallBack);

	/** Hide the loading screen */
	void HideLoadingScreen();

	/** Show the game options UI */
	void ShowGameOptions();

private:
	void OnMapPostLoad(UWorld* World);
	void ShowKeyBindsWidget();
	void ShowSettingsWidget();
	void PushWidgetOntoStack(const TWeakObjectPtr<UUserWidget>& Widget);
	void NavigateBack();

private:
	template <typename WidgetType, typename = TEnableIf<TIsDerivedFrom<WidgetType, UUserWidget>::IsDerived, WidgetType>>
	WidgetType* CreateWidgetOfClass(const TSubclassOf<UUserWidget>& WidgetClass, int32 ZOrder) const
	{
		WidgetType* Widget { CreateWidget<WidgetType>(GetGameInstance(), WidgetClass) };
		Widget->AddToViewport(ZOrder);
		Widget->SetVisibility(ESlateVisibility::Collapsed);
		return Widget;
	}

private:
	bool IsLoadingScreenActive { false };
	FTimerHandle TimerHandle;
	TArray<TWeakObjectPtr<UUserWidget>> NavigationStack;

	TWeakObjectPtr<UOptionsMenuWidget> OptionsWidget;
	TWeakObjectPtr<UGameSettingsWidget> GameSettingsWidget;
	TWeakObjectPtr<UKeyBindsWidget> KeyBindsWidget;
	TWeakObjectPtr<UUserWidget> LoadingScreenWidget;
};
