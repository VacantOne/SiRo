// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameInstanceManager.h"
#include "Modules/ModuleManager.h"

// #define LOCTEXT_NAMESPACE "FMyModule"

void FGameInstanceManager::StartupModule()
{
    // 模块启动时的初始化代码
    //UE_LOG(LogTemp, Warning, TEXT("================== MyModule module started"));
}

void FGameInstanceManager::ShutdownModule()
{
    // 模块关闭时的清理代码
    //UE_LOG(LogTemp, Warning, TEXT("================== MyModule module shutdown"));
}

// IMPLEMENT_MODULE(FMyModule, MyModule)
IMPLEMENT_GAME_MODULE(FGameInstanceManager, GameInstanceManager);
