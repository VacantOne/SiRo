// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameInstanceManager : ModuleRules
{
	public GameInstanceManager(ReadOnlyTargetRules Target) : base(Target)
	{
        OptimizeCode = CodeOptimization.InShippingBuildsOnly;
        bUseUnity = false;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicIncludePaths.AddRange(new string[] { "GameInstanceManager" });
        PrivatePCHHeaderFile = "GameInstanceManager.h";

        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UMG"});
		PrivateDependencyModuleNames.AddRange(new string[] {
            "MyCore", "GameSystem", "GameBase", "GameComponent"
        });

    }
}
