//
// Door.h
// Definition of the ADoor class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetasoundSource.h"

#include "FrozenDread/Gameplay/InteractiveObject.h"

#include "Door.generated.h"

/** The states for the door's lock state. */
UENUM(BlueprintType)
enum class EDoorLockState : uint8
{
	Unlocked			UMETA(DisplayName = "Unlocked"),
	Locked				UMETA(DisplayName = "Locked"),
	RequiresKeyCard		UMETA(DisplayName = "Requires KeyCard")
};

/** The direction for moving the door */
UENUM(BlueprintType)
enum class EDoorMoveDirection : uint8
{
	Right,
	Up
};

class UBoxComponent;
class USceneComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class UTimelineComponent;

UCLASS()
class FROZENDREAD_API ADoor : public AActor, public IInteractiveObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	// Unlock the door (can only be done if state is locked)
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void Unlock();

	// IInteractiveObject implementation

	// Interact with the door. If Requires keycard, then the player must hold the keycard in their inventory.
	virtual void Interact(APlayerCharacter* PlayerCharacter) override;

	// Set this door to be highlighted
	virtual void SetHighlighted(bool IsHighlighted) override;

	// The display text to show for the 
	virtual FText DisplayText() const override;

protected:
	// The player interacted with the door 
	UFUNCTION(BlueprintNativeEvent, Category="Interaction")
	void PlayerInteractedWithDoor();

private:
	bool PlayerHasKeyCard(const APlayerCharacter* PlayerCharacter) const;
	void CoolDownComplete() { CanInteract = true; }
	void SetLockStatusWidgets(bool IsLocked) const;

private:
	/** The direction the door moves in when opened */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	EDoorMoveDirection MoveDirection { EDoorMoveDirection::Right };

	/** The locked status for the door */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	EDoorLockState LockState { EDoorLockState::Unlocked };

	/** The (optional) ID for the key card needed to open this door (if state is RequiresKeyCard) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	uint8 KeyCardID { 0 };

	/** The sound that plays when the door is unlocked */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UMetaSoundSource> UnlockSound;

	/** The sound that plays when the door denies access and remains locked */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UMetaSoundSource> AccessDeniedSound;

	/** The root component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> SceneComponent;
	
	/** The mesh to use for the door */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	/** The Box collision for the door to enable interaction */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBoxComponent> InteractionBox;

	/** The text to display when the player looks at the door and it is open */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	FText OpenStateText;

	/** The text to display when the player looks at the door and it is closed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	FText ClosedStateText;

	/** The timeout before the player can interact with the item again */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	float CoolDownTimeSeconds { 2.0F };

	/** True if the door is currently opened or closed */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Interaction", meta=(AllowPrivateAccess="true"))
	bool IsOpen { false };

	/** The UMG Widget for the door's lock / unlock world UI (front)*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UWidgetComponent> LockStatusWidgetFront;

	/** The UMG Widget for the door's lock / unlock world UI (back)*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UWidgetComponent> LockStatusWidgetBack;

private:
	FTimerHandle CoolDownTimer;
	bool CanInteract { true };
};
