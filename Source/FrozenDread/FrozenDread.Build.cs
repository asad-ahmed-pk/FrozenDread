// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FrozenDread : ModuleRules
{
	public FrozenDread(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "MetasoundEngine", "UMG", "GameplayTasks" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "AIModule", "NavigationSystem", "GameplayTags", "LevelSequence", "MovieScene" });
	}
}
