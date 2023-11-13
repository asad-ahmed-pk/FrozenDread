//
// GameHUD.h
// Definition of the AGameHUD class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UPauseMenuWidget;
class UUserWidget;
class UInteractionWidget;
class UInventoryWidget;
class UDialogueWidget;
class UGameOverWidget;
class UObjectiveWidget;
class UCinematicWidget;

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

	/** Get the reference to the pause menu Widget */
	UPauseMenuWidget* GetPauseMenuWidget() const;

	/** Get the reference to the objectives Widget */
	UObjectiveWidget* GetObjectiveWidget() const;

	/** Get the reference to the cinematic Widget */
	UCinematicWidget* GetCinematicWidget() const;

protected:
	/** The BP class to use for the interaction widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> InteractionWidgetClass;

	/** The BP class to use for the inventory widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	/** The BP class to use for the dialogue widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> DialogueWidgetClass;

	/** The BP class to use for the pause menu widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	/** The BP class to use for the game over widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	/** The BP class to use for the objectives list widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> ObjectiveWidgetClass;

	/** The BP class to use for the cinematic widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> CinematicWidgetClass;

private:
	UPROPERTY()
	UUserWidget* InteractionWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> InventoryWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> DialogueWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> PauseMenuWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> GameOverWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> ObjectiveWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> CinematicWidget;
};
