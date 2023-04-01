//
// GamePlayerState.h
// Definition of the AGamePlayerState class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GamePlayerState.generated.h"

/**
 * Main player state class for the game.
 */
UCLASS()
class FROZENDREAD_API AGamePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	/// Returns true if the player is wearing a suit
	FORCEINLINE bool GetIsWearingSuit() const { return IsWearingExoSuit; }

	/// Set if the player is wearing the ExoSuit
	FORCEINLINE void SetIsWearingSuit(bool bIsWearing) { IsWearingExoSuit = bIsWearing; }

private:
	bool IsWearingExoSuit { false };
};
