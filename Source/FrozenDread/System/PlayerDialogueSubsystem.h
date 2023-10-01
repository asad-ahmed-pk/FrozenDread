//
// PlayerDialogueSubsystem.h
// Definition of the UPlayerDialogueSubsystem class.
//

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Misc/Optional.h"

#include "FrozenDread/Game/Dialogue.h"
#include "FrozenDread/Player/GamePlayerController.h"

#include "PlayerDialogueSubsystem.generated.h"

class UDialogueWidget;
class AGamePlayerController;

// Callback for dialogue completion
DECLARE_DYNAMIC_DELEGATE(FDialogueCallBack);

/**
 * Subsystem for displaying player dialogue during gameplay
 */
UCLASS()
class FROZENDREAD_API UPlayerDialogueSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	/** Determine if subsystem should be created or not */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/** Determine if this subsystem is tickable when paused */
	virtual bool IsTickableWhenPaused() const override { return true; }

	virtual bool IsTickable() const override { return IsCurrentlyPlaying; }

	/** Required override for tickable sub-system */
	virtual TStatId GetStatId() const override { return TStatId(); }

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Setup this subsystem with the given dialogue widget to manage */
	UFUNCTION(BlueprintCallable, Category="Setup")
	void Setup(UDialogueWidget* DialogueWidgetPtr, AGamePlayerController* LocalPlayerController);

	/** Add text to the dialogue queue */
	void AddDialogueItem(const FDialogueItem& DialogueItem, const TOptional<const FDialogueCallBack>& CallBackRef);

private:
	void BeginDialogueMode();
	void EndDialogueMode();
	void UpdateUI();
	void NextDialogueItemRequested();

private:
	TQueue<FDialogueItem, EQueueMode::Mpsc> DialogueQueue;
	UDialogueWidget* DialogueWidget { nullptr };
	FDialogueItem LastPlayedItem;
	TOptional<const FDialogueCallBack> CallBack {};

	TWeakObjectPtr<AGamePlayerController> PlayerController;

	bool IsCurrentlyPlaying { false };
};
