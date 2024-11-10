// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class MyEditor : ModuleRules
{
	public MyEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		OptimizeCode = CodeOptimization.InShippingBuildsOnly;
		bUseUnity = false;

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = false;
		PrivatePCHHeaderFile = "MyEditor.h";
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "ToolMenus", 
		});
		//加入项目dll
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"MyCore", "GameBase", "GameSystem",	"GameInstanceManager"
			// ,"GameComponent",
		});
	}
}