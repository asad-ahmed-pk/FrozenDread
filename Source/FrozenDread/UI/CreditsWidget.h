//
// CreditsWidget.h
// Definition of the UCreditsWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FrozenDread/Game/MainUserInterface.h"
#include "CreditsWidget.generated.h"

class UButton;

/**
 * Widget for showing game credits
 */
UCLASS()
class FROZENDREAD_API UCreditsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FBackButtonClickDelegate OnBackButtonClicked;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void BackButtonClicked();

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> BackButton;
};
