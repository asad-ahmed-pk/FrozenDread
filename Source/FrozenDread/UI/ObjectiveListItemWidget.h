//
// ObjectiveListItemWidget.h
// Definition of the UObjectiveListItemWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"

#include "ObjectiveListItemWidget.generated.h"

class UCheckBox;
class UTextBlock;

/**
 * Widget for displaying a single game objective
 */
UCLASS()
class FROZENDREAD_API UObjectiveListItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	/** Set the given list entry as completed */
	void SetAsCompleted() const;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
	/** The outer level checkbox (for top level objectives) */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UCheckBox> OuterCheckBox;

	/** The inner level checkbox (for child objectives) */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UCheckBox> InnerCheckBox;

	/** The text to display the objective */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> ObjectiveText;
};
