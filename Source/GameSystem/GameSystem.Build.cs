// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GameSystem : ModuleRules
{
	public GameSystem(ReadOnlyTargetRules Target) : base(Target)
	{
        OptimizeCode = CodeOptimization.InShippingBuildsOnly;
        bUseUnity = false;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicIncludePaths.AddRange(new string[] { "GameSystem"});
        PrivatePCHHeaderFile = "GameSystem.h";
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "EngineSettings", "EnhancedInput"
        });
        PrivateDependencyModuleNames.AddRange(new string[] {
            "MyCore"//, "GameBase", "GameComponent"
        });		
    }
}
