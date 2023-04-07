//
// GameHUD.h
// Definition of the AGameHUD class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UUserWidget;
class UInteractionWidget;

/**
 * The main HUD to use during gameplay.
 */
UCLASS()
class FROZENDREAD_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** Init this HUD and all its widgets and add them to the view port */
	void InitAndAddToViewport();

	/** Set the visibility of the given */
	void SetInteractionWidgetVisible(bool IsVisible) const;

	UInteractionWidget* GetInteractionWidget() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> InteractionWidgetClass;

private:
	UPROPERTY()
	UUserWidget* InteractionWidget;
};
