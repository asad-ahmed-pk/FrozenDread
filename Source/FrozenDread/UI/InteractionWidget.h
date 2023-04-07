//
// InteractionWidget.h
// Definition of the UInteractionWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class UTextBlock;
class UImage;

/**
 * A user widget that displays the interaction info for the player.
 * ie; what items the player is currently looking at.
 */
UCLASS()
class FROZENDREAD_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Set the visibility of this widget */
	FORCEINLINE void Show(bool IsVisible) { SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden); }

	/** Set the interaction text */
	void SetInteractionText(const FText& Text) const;

protected:
	virtual void NativeConstruct() override;

protected:
	/** An image showing a icon for the 'use' action */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> UseIconImage;
	
	/** The name of the interactive object that the player is currently looking at */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> InteractionText;
};
