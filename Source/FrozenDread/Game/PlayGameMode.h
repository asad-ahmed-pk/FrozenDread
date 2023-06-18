//
// PlayGameMode.h
// Definition of the APlayGameMode class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayGameMode.generated.h"

UCLASS(minimalapi)
class APlayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlayGameMode();

	virtual void BeginPlay() override;
};
