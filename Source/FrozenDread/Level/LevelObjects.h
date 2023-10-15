//
// LevelObjects.h
// Enum for representing level object IDS
//

#pragma once

/** Level Names */
namespace LevelNames
{
	constexpr char* MAIN_MENU { "MainMenu" };
	constexpr char* GAME { "SciFiBase" };
}

/** ID for gameplay / level objects that can be interacted with */
UENUM(BlueprintType)
enum class EInteractionItemID : uint8
{
	OtherDoor						UMETA(DisplayName = "Other Non Essential Door"),
	BrokenDoor						UMETA(DisplayName = "Broken Door"),
	BrokenDoorPanel					UMETA(DisplayName = "Broken Door Repair Panel"),
	ControlRoomDoor					UMETA(DisplayName = "Control Room Door"),
	ControlRoomPanel				UMETA(DisplayName = "Control Room Panel")
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
	constexpr char* TAG_TRIGGER_EARLY_EXIT { "EarlyExitTrigger" };
	constexpr char* TAG_TRIGGER_RED_ALERT { "RedAlertTrigger" };
	constexpr char* TAG_TRIGGER_FLASHLIGHT_DIALOGUE { "FlashlightDialogueTrigger" };
	constexpr char* TAG_TRIGGER_2ND_MONSTER_SPAWN { "SpawnSecondMonsterTrigger" };

	constexpr char* TAG_ACTOR_DOOR_REPAIR_PANEL { "BrokenPanelDoor" };
	constexpr char* TAG_ACTOR_AMBIENT_SOUND_RED_ALERT { "RedAlertSound" };
	constexpr char* TAG_ACTOR_RECT_LIGHT_RED_ALERT { "RedAlertRectLight" };
	constexpr char* TAG_ACTOR_EXIT_BLOCKING_VOLUME { "ExitBlockingVolume" };

	constexpr char* TAG_MONSTER_1_SPAWN_LOCATION { "Monster1Spawn" };
	constexpr char* TAG_MONSTER_1_Waypoints { "Monster1Waypoints" };

	constexpr char* TAG_MONSTER_2_SPAWN_LOCATION { "Monster2Spawn" };
	constexpr char* TAG_MONSTER_2_Waypoints { "Monster2Waypoints" };
}
