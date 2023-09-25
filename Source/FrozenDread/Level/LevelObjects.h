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

/** ID for trigger volumes and boxes */
UENUM(BlueprintType)
enum class ETriggerVolumeID : uint8
{
	JumpScareTrigger				UMETA(DisplayName = "First Jumpscare"),
	RedAlertTrigger					UMETA(DisplayName = "Red Alert Trigger"),
	EarlyExitTrigger				UMETA(DisplayName = "Early Exit Trigger"),
	MusicStartTrigger				UMETA(DisplayName = "Music Start Trigger")
};

/** The ID for inventory items */
UENUM(BlueprintType)
enum class InventoryItemID : uint8
{
	Toolbox							UMETA(DisplayName = "Toolbox"),
	ControlRoomKeyCard				UMETA(DisplayName = "Control Room Keycard")
};