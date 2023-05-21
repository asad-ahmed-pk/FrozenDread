//
// GameItems.h
// Enums and constants defining items for the game
//

#pragma once

// Game item types
UENUM(BlueprintType)
enum class EGameItemType : uint8
{
	Default = 0							UMETA(DisplayName = "Default (Unset) Game Item"),
	KeyCard = 1							UMETA(DisplayName = "Key Card"),
	DataLog = 2							UMETA(DisplayName = "DataLog"),
};

// Key Cards
UENUM(BlueprintType)
enum class EKeyCardID : uint8
{
	None = 0							UMETA(DisplayName = "Null ID"),
	PlayerRoom = 1						UMETA(DisplayName = "Player's Room"),
	NurseRoom = 2						UMETA(DisplayName = "Nurse's Room")
};

