// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GameComponent : ModuleRules
{
	public GameComponent(ReadOnlyTargetRules Target) : base(Target)
	{
        OptimizeCode = CodeOptimization.InShippingBuildsOnly;
        bUseUnity = false;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicIncludePaths.AddRange(new string[] { "GameComponent"});
        PrivatePCHHeaderFile = "GameComponent.h";
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "EngineSettings", "EnhancedInput", "UMG"
        });
        PrivateDependencyModuleNames.AddRange(new string[] {
            "MyCore"//, "GameBase", "GameComponent"
        });
        // 添加公共头文件路径
        PublicIncludePaths.AddRange(new string[] {
            //"UI", "DataConfig" // 假设您的模块名为MyModule
        });
    }
}
