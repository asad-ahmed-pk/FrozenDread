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

// Callback for dialogue completion
DECLARE_DYNAMIC_DELEGATE(FDialogueCallBack);

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
	UFUNCTION(BlueprintCallable, Category="Dialogue", meta=(AutoCreateRefTerm="CallBackRef"))
	void AddDialogueItem(const FDialogueItem& DialogueItem, const FDialogueCallBack& CallBackRef);

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
	TOptional<const FDialogueCallBack> CallBack {};
};
