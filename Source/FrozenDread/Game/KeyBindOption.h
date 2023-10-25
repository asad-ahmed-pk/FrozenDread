// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedActionKeyMapping.h"
#include "UObject/Object.h"
#include "KeyBindOption.generated.h"

/**
 * Represents a key-bind option for UI
 */
UCLASS()
class FROZENDREAD_API UKeyBindOption : public UObject
{
	GENERATED_BODY()

public:
	void SetKeyMapping(int32 OptionIndex, const FEnhancedActionKeyMapping& Mapping) { KeyMapping = Mapping; Index = OptionIndex; }
	FEnhancedActionKeyMapping GetKeyMapping() const { return KeyMapping; }

private:
	int32 Index { 0 };
	FEnhancedActionKeyMapping KeyMapping;
};
