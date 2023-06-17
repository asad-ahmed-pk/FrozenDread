//
// PlayerCharacter.h
// Definition of the APlayerCharacter class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class UInputAction;
class UInputComponent;
class UInputMappingContext;
class UInteractionComponent;
class UInventory;
class UAISense;
class UAIPerceptionStimuliSourceComponent;

UCLASS()
class FROZENDREAD_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Switch the mesh to ExoSuit
	void SwitchToExoSuit() const;

	// Get a reference to the player's inventory system
	UInventory* GetInventory() const;

	// Get a reference to the interaction component
	FORCEINLINE UInteractionComponent* GetInteractionComponent() const { return InteractionComponent.Get(); }

private:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for pressing the 'use' key */
	void Use(const FInputActionValue& Value);

private:
	/** Main FPS Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> MainCamera;

	/** ExoSuit Mesh */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> ExoSuitMesh;

	/** Interaction component for interacting with the world */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInteractionComponent> InteractionComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	/** Use Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> UseAction;

	/** The perception stimulant to get the player detected by the monster */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAIPerceptionStimuliSourceComponent> PerceptionStimuliSource;
};
