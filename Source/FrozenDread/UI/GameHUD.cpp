//
// GameHUD.cpp
// Implementation of the AGameHUD class.
//


#include "FrozenDread/UI/GameHUD.h"

#include "FrozenDread/UI/InteractionWidget.h"
#include "FrozenDread/Player/GamePlayerController.h"

void AGameHUD::InitAndAddToViewport()
{
	check(InteractionWidgetClass);

	AGamePlayerController* PlayerController { Cast<AGamePlayerController>(GetOwner()) };
	
	InteractionWidget = CreateWidget<UUserWidget>(PlayerController, InteractionWidgetClass);
	InteractionWidget->AddToViewport();
}

void AGameHUD::SetInteractionWidgetVisible(bool IsVisible) const
{
	check(InteractionWidget);
	InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
}

UInteractionWidget* AGameHUD::GetInteractionWidget() const
{
	check(InteractionWidget);
	return Cast<UInteractionWidget>(InteractionWidget);
}
