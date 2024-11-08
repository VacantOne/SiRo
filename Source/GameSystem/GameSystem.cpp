#include "GameSystem.h"
#include "Modules/ModuleManager.h"

// #define LOCTEXT_NAMESPACE "FMyModule"

void FGameSystem::StartupModule()
{
    // 模块启动时的初始化代码
}

void FGameSystem::ShutdownModule()
{
    // 模块关闭时的清理代码
}


IMPLEMENT_GAME_MODULE(FGameSystem, GameSystem);
