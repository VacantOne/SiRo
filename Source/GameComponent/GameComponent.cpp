#include "GameComponent.h"
#include "Modules/ModuleManager.h"

// #define LOCTEXT_NAMESPACE "FMyModule"

void FGameComponent::StartupModule()
{
    // 模块启动时的初始化代码
}

void FGameComponent::ShutdownModule()
{
    // 模块关闭时的清理代码
}


IMPLEMENT_GAME_MODULE(FGameComponent, GameComponent);
