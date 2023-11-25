//
// EndGamePlayerController.h
// Definition of the AEndGamePlayerController class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EndGamePlayerController.generated.h"

/**
 * The player controller to use for the end game scene
 */
UCLASS()
class FROZENDREAD_API AEndGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category="Widgets")
	void WidgetSetupComplete();

private:
	/** The widget class to use for the end game UI */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUserWidget> EndGameWidgetClass;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Widgets")
	TObjectPtr<UUserWidget> EndGameWidget;
};
