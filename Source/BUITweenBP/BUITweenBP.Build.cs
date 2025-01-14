// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BUITweenBP : ModuleRules
{
	public BUITweenBP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG",
				"BUITween"
			}
		);
	}
}