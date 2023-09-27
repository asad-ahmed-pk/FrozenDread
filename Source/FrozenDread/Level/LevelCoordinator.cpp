//
// LevelCoordinator.cpp
// Implementation of the ALevelCoordinator class.
//

#include "FrozenDread/Level/LevelCoordinator.h"

void ALevelCoordinator::Init(const FSubsystemCache& SubsystemCacheRef)
{
	SubsystemCache = SubsystemCacheRef;
}

void ALevelCoordinator::PlayerInteractedWithDoor(uint8 DoorID, EDoorLockState DoorLockState)
{
	UE_LOG(LogTemp, Warning, TEXT("ALevelCoordinator::PlayerInteractedWithDoor called. Please override in child class."));
}

void ALevelCoordinator::PlayerInteractedWithItem(uint8 ItemID, AInteractionItem* Item)
{
	UE_LOG(LogTemp, Warning, TEXT("ALevelCoordinator::PlayerInteractedWithItem called. Please override in child class."));
}
