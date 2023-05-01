// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BananaStrike : ModuleRules
{
	public BananaStrike(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "Niagara" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "GameplayTasks" });
	}
}
