// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyCore : ModuleRules
{
	public MyCore(ReadOnlyTargetRules Target) : base(Target)
	{

        OptimizeCode = CodeOptimization.InShippingBuildsOnly;
        bUseUnity = false;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        // 依赖的模块（如 CoreUObject，Engine 等）
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

        // 私有依赖模块
        PrivateDependencyModuleNames.AddRange(new string[] {});
	}
}