//
// KeyBindOptionWidget.h
// Definition of the UKeyBindOptionWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "EnhancedActionKeyMapping.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"

#include "KeyBindOptionWidget.generated.h"

class UTextBlock;
class UButton;

DECLARE_MULTICAST_DELEGATE_OneParam(FKeyBindOptionButtonClicked, UUserWidget*);

/**
 * Represents a key binding option for a key.
 */
UCLASS()
class FROZENDREAD_API UKeyBindOptionWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	void SetKeyBindForAction(const FEnhancedActionKeyMapping& Action) const;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	UFUNCTION()
	void KeyBindButtonClicked();

public:
	FKeyBindOptionButtonClicked OnKeyBindButtonClicked;

protected:
	/** The name of the input action */
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> InputActionNameText;
	
	/** The button to click to set the key bind */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> KeyBindButton;

	/** The text for the key bind button */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> KeyBindButtonText;
};

