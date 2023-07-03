//
// PlayerDialogueSubsystem.h
// Definition of the UPlayerDialogueSubsystem class.
//

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "FrozenDread/Game/Dialogue.h"

#include "PlayerDialogueSubsystem.generated.h"

class UDialogueWidget;

// Player dialogue finished playing (with the unique name of the dialogue)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDialogueFinishedPlaying, FDialogueItem, DialogueItem);

/**
 * Subsystem for displaying player dialogue during gameplay
 */
UCLASS()
class FROZENDREAD_API UPlayerDialogueSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/** Determine if subsystem should be created or not */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/** Setup this subsystem with the given dialogue widget to manage */
	UFUNCTION(BlueprintCallable, Category="Setup")
	void Setup(UDialogueWidget* DialogueWidgetPtr);

	/** Add text to the dialogue queue */
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void AddDialogueItem(const FDialogueItem& DialogueItem);

	/** Delegate for when the player dialogue item finishes playing */
	UPROPERTY(BlueprintAssignable)
	FPlayerDialogueFinishedPlaying OnDialogueFinished;

private:
	void PlayNextDialogueText();
	void TextTypeTimer();
	void NextDialogueItemRequested();

private:
	FTimerHandle DialogueTextTimer;
	TQueue<FDialogueItem, EQueueMode::Mpsc> DialogueQueue;
	UDialogueWidget* DialogueWidget { nullptr };
	uint32 CurrentTextLength { 0 };
	FDialogueItem LastPlayedItem;
};
