#include "MyCore.h"
#include "Modules/ModuleManager.h"

// #define LOCTEXT_NAMESPACE "FMyModule"

void FMyCore::StartupModule()
{
    // 模块启动时的初始化代码
    //UE_LOG(LogTemp, Warning, TEXT("================== MyModule module started"));
}

void FMyCore::ShutdownModule()
{
    // 模块关闭时的清理代码
    //UE_LOG(LogTemp, Warning, TEXT("================== MyModule module shutdown"));
}

// IMPLEMENT_MODULE(FMyModule, MyModule)
IMPLEMENT_GAME_MODULE(FMyCore, MyCore);
