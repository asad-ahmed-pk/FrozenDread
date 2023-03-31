// Copyright Epic Games, Inc. All Rights Reserved.

#include "FrozenDreadGameMode.h"
#include "FrozenDreadCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFrozenDreadGameMode::AFrozenDreadGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
