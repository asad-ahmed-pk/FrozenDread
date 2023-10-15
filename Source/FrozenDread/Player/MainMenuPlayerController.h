//
// MainMenuPlayerController.cpp
// Definition of the AMainMenuPlayerController class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

class UUserWidget;

/**
 * The player controller to use for the main menu level
 */
UCLASS()
class FROZENDREAD_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	/** The widget class to use for the main menu */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

private:
	TObjectPtr<UUserWidget> MainMenuWidget;
};
