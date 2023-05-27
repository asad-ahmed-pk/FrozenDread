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
	
	virtual void Tick(float DeltaTime) override;

	// Switch to wearing the exo suit.
	void SwitchPlayerSuit() const;

	// Get a reference to the player's inventory system
	FORCEINLINE UInventory* GetInventory() const { return Inventory; }

protected:
	virtual void SetupInputComponent() override;

private:
	void ToggleInventory();

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MappingContext;

	/** Inventory Toggle Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InventoryToggleAction;

private:
	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;
	TWeakObjectPtr<AGamePlayerState> GamePlayerState;
	TWeakObjectPtr<AGameHUD> GameHUD;

	TObjectPtr<UInventory> Inventory;

	bool IsViewingInventory { false };

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	IConsoleVariable* IsWearingSuitCVar { nullptr };
#endif
};
