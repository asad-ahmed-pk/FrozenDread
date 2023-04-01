//
// GamePlayerController.h
// Definition of the AGamePlayerController class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

class APlayerCharacter;
class AGamePlayerState;

/**
 * Main player controller class for the game
 */
UCLASS()
class FROZENDREAD_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	// Switch to wearing the exo suit.
	void SwitchPlayerSuit() const;

private:
	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;
	TWeakObjectPtr<AGamePlayerState> GamePlayerState;
};
