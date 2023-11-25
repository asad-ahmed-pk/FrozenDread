//
// GamePlayerController.h
// Definition of the AGamePlayerController class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

class APlayerCharacter;
class AGamePlayerState;
class AGameHUD;
class IConsoleVariable;
class UInputMappingContext;
class UInputAction;
class UInventory;
class USoundBase;

/** Delegate that is called once the HUD and player UI is setup and ready */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerUIReadyDelegate);

/**
 * Main player controller class for the game
 */
UCLASS()
class FROZENDREAD_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGamePlayerController();
	
	virtual void BeginPlay() override;

	/** Set the mouse pointer on the center of the view port */
	void SetMousePointerOnCenter();

	/** Display the main menu or back to the gameplay */
	void SetMainMenuIsActive(bool IsActive);

	/** Trigger game complete cinematics */
	void StartGameCompleteSequence() const;
	
	/** Get a reference to the player's inventory system */
	FORCEINLINE UInventory* GetInventory() const { return Inventory; }
	

protected:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void ToggleInventory();

	virtual void SetupInputComponent() override;

private:
	void PlayIntro();

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MappingContext;

	/** Inventory Toggle Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InventoryToggleAction;
	
	/** Sound to play when the player opens or closes the inventory */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sound", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundBase> InventoryToggleSound;

	/** The player's inventory */
	UPROPERTY(Transient)
	TObjectPtr<UInventory> Inventory;

private:
	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;
	TWeakObjectPtr<AGamePlayerState> GamePlayerState;
	TWeakObjectPtr<AGameHUD> GameHUD;
	
	bool IsViewingInventory { false };
};
