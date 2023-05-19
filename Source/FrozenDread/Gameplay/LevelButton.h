//
// LevelButton.h
// Definition of the ALevelButton class.
//

#pragma once

#include "CoreMinimal.h"
#include "MetasoundSource.h"
#include "InteractiveObject.h"

#include "LevelButton.generated.h"

/** Delegate for responding to button interaction */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonPressedEvent);

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class FROZENDREAD_API ALevelButton : public AActor, public IInteractiveObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelButton();

	virtual void SetHighlighted(bool IsHighlighted) override;

	virtual FText DisplayText() const override;

	virtual void Interact(APlayerCharacter* PlayerCharacter) override;

public:
	/** The delegate for responding to this button's interaction */
	UPROPERTY(BlueprintAssignable)
	FButtonPressedEvent OnButtonPressed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void CoolDownCompleted() { IsInCoolDown = false; }

private:
	/** The text to display when the player looks at the button */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	FText InteractionText;

	/** The sound the button plays when interacted with */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UMetaSoundSource> InteractionSound;

	/** The box used to detect the interaction */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBoxComponent> BoxComponent;

	/** The mesh to use for the button */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	/** The collision channel to use for the interaction detection */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	/** The cooldown period for the button */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	float CoolDownTimeSeconds { 2.0F };

private:
	bool IsInCoolDown { false };
	FTimerHandle CoolDownTimerHandle;
};
