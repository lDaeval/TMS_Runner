// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TMS_Runner : ModuleRules
{
	public TMS_Runner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"DeveloperSettings"
		});
	}
}
