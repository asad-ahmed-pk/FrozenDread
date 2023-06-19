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
class UDialogueWidget;
class UGameOverWidget;

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

	/** Get the reference to the dialogue Widget */
	UDialogueWidget* GetDialogueWidget() const;

	/** Get the reference to the game over Widget */
	UGameOverWidget* GetGameOverWidget() const;

protected:
	/** The BP class to use for the interaction widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> InteractionWidgetClass;

	/** The BP class to use for the inventory widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	/** The BP class to use for the dialogue widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> DialogueWidgetClass;

	/** The BP class to use for the game over widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> GameOverWidgetClass;

private:
	UPROPERTY()
	UUserWidget* InteractionWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> InventoryWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> DialogueWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> GameOverWidget;
};
