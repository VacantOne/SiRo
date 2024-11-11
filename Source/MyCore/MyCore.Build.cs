// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class MyCore : ModuleRules
{
	public MyCore(ReadOnlyTargetRules Target) : base(Target)
	{

        OptimizeCode = CodeOptimization.InShippingBuildsOnly;
        bUseUnity = false;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        PublicIncludePaths.Add(ThirdPartyPath + "entt");
        PublicIncludePaths.AddRange(new string[] { "Runtime/MyCore" });
        PrivatePCHHeaderFile = "MyCore.h";

        // 依赖的模块（如 CoreUObject，Engine 等）
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

        // 私有依赖模块
        PrivateDependencyModuleNames.AddRange(new string[] {});
	}

        public string ThirdPartyPath
        {
                get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/")); }
        }
}