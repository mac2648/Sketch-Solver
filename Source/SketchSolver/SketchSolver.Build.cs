// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SketchSolver : ModuleRules
{
	public SketchSolver(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
