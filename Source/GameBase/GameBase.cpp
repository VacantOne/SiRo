#include "GameBase.h"
#include "Modules/ModuleManager.h"


void FGameBase::StartupModule()
{
    // 模块启动时的初始化代码
    //UE_LOG(LogTemp, Warning, TEXT("================== MyModule module started"));
}

void FGameBase::ShutdownModule()
{
    // 模块关闭时的清理代码
    //UE_LOG(LogTemp, Warning, TEXT("================== MyModule module shutdown"));
}

IMPLEMENT_GAME_MODULE(FGameBase, GameBase);
