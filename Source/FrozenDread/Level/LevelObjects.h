//
// LevelObjects.h
// Enum for representing level object IDS
//

#pragma once

/** ID for gameplay / level objects that can be interacted with */
UENUM(BlueprintType)
enum class EInteractionItemID : uint8
{
	OtherDoor						UMETA(DisplayName = "Other Non Essential Door"),
	BrokenDoor						UMETA(DisplayName = "Broken Door"),
	BrokenDoorPanel					UMETA(DisplayName = "Broken Door Repair Panel"),
	ControlRoomMainDoor				UMETA(DisplayName = "Control Room Main Door"),
	ControlRoomBottomDoor			UMETA(DisplayName = "Control Room Bottom Door"),
	ControlRoomTopDoor				UMETA(DisplayName = "Control Room Top Door"),
	ControlRoomControlPanel			UMETA(DisplayName = "Control Room Control Panel"),
};

/** The ID for inventory items */
UENUM(BlueprintType)
enum class InventoryItemID : uint8
{
	Toolbox							UMETA(DisplayName = "Toolbox"),
	ControlRoomKeyCard				UMETA(DisplayName = "Control Room Keycard")
};

/** ID Tags for trigger volumes and boxes */
namespace Tags
{
	constexpr char* TAG_TRIGGER_JUMP_SCARE { "JumpScareTrigger" };
	constexpr char* TAG_TRIGGER_EARLY_EXIT { "EarlyExitTrigger" };
	constexpr char* TAG_TRIGGER_RED_ALERT { "RedAlertTrigger" };
	constexpr char* TAG_TRIGGER_MUSIC_START { "MusicStartTrigger" };

	constexpr char* TAG_ACTOR_AMBIENT_SOUND_RED_ALERT { "RedAlertSound" };
	constexpr char* TAG_ACTOR_RECT_LIGHT_RED_ALERT { "RedAlertRectLight" };

	constexpr char* TAG_MONSTER_1_SPAWN_LOCATION { "Monster1Spawn" };
	constexpr char* TAG_MONSTER_1_Waypoints { "Monster1Waypoints" };

	constexpr char* TAG_MONSTER_2_SPAWN_LOCATION { "Monster2Spawn" };
	constexpr char* TAG_MONSTER_2_Waypoints { "Monster2Waypoints" };
}
