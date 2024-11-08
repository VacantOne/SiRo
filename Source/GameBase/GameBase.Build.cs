// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GameBase : ModuleRules
{
	public GameBase(ReadOnlyTargetRules Target) : base(Target)
	{
        OptimizeCode = CodeOptimization.InShippingBuildsOnly;
        bUseUnity = false;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicIncludePaths.AddRange(new string[] { "GameBase" });
        PrivatePCHHeaderFile = "GameBase.h";
		PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "InputCore"
        });
        
        PublicDependencyModuleNames.AddRange((new []{"Core"}));

        PrivateDependencyModuleNames.AddRange(new string[] {
            "MyCore"
        });
        
        if (Target.bBuildEditor == true)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[] { "DeveloperToolSettings"});
        }
    }
}
