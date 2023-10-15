//
// GameUISubsystem.cpp
// Implementation of the UGameUISubsystem class.
//

#include "GameUISubsystem.h"

#include "Blueprint/UserWidget.h"

void UGameUISubsystem::Init(UUserWidget* LoadingWidget)
{
	LoadingScreenWidget = LoadingWidget;
	
	// Subscribe to level loading events
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UGameUISubsystem::OnMapPostLoad);
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

void UGameUISubsystem::OnMapPostLoad(UWorld* World)
{
	// Hide loading screen
	HideLoadingScreen();
}
