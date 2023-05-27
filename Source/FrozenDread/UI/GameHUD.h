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
class UInventoryWidget;

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

	/** Set the visibility of the inventory widget */
	void SetInventoryWidgetVisible(bool IsVisible) const;

	/** Get the reference to the Interaction Widget */
	UInteractionWidget* GetInteractionWidget() const;

	/** Get the reference to the Inventory Widget */
	UInventoryWidget* GetInventoryWidget() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> InteractionWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> InventoryWidgetClass;

private:
	UPROPERTY()
	UUserWidget* InteractionWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> InventoryWidget;
};
