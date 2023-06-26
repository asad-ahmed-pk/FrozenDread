// Copyright Epic Games, Inc. All Rights Reserved.

#include "FrozenDreadGameMode.h"

#include "FrozenDread/Player/PlayerCharacter.h"

AFrozenDreadGameMode::AFrozenDreadGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
}
