//
// GameItems.h
// Enums and constants defining items for the game
//

#pragma once

// Key Cards
UENUM(BlueprintType)
enum class EKeyCardID : uint8
{
	None = 0							UMETA(DisplayName = "Null ID"),
	PlayerRoom = 1						UMETA(DisplayName = "Player's Room")
};

