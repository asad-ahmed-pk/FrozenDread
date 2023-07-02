//
// ObjectiveWidget.h
// Definition of the UObjectiveWidget class.
//

#pragma once

class UListView;
class UVerticalBox;

#include "FrozenDread/Game/Objective.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ObjectiveWidget.generated.h"

/**
 * Widget for displaying the objectives for the player.
 */
UCLASS()
class FROZENDREAD_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Add the given objective to the objectives list */
	void AddObjective(const FGameObjective& Objective) const;

	/** Marks the objective as completed and removes it from the list */
	void MarkObjectiveCompleted(uint8 ObjectiveID) const;

protected:
	virtual void NativeConstruct() override;

protected:
	/** The list view that displays objectives */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UListView> ObjectiveListView;
};
