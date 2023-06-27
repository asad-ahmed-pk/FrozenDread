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
class UMetaSoundSource;

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

	// Get a reference to the player's inventory system
	FORCEINLINE UInventory* GetInventory() const { return Inventory; }

protected:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void ToggleInventory();

	virtual void SetupInputComponent() override;

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MappingContext;

	/** Inventory Toggle Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InventoryToggleAction;
	
	/** Sound to play when the player opens or closes the inventory */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sound", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UMetaSoundSource> InventoryToggleSound;

private:
	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;
	TWeakObjectPtr<AGamePlayerState> GamePlayerState;
	TWeakObjectPtr<AGameHUD> GameHUD;

	TObjectPtr<UInventory> Inventory;

	bool IsViewingInventory { false };
};
