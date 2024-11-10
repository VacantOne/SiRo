#include "MyEditor.h"
#include "Modules/ModuleManager.h"
#include "MyCore/AdminWorld.h"
#include "Editor.h"

void FMyEditorModule::StartupModule()
{
	// 避免命令行-run=xxx模式运行编辑器时执行异常逻辑。如关卡构建同步，lua生成智能语法提示等
	if (IsRunningCommandlet())
	{
		return;
	}
	FCoreDelegates::OnFEngineLoopInitComplete.AddRaw(this, &FMyEditorModule::OnEngineLoopInitComplete);
	FCoreDelegates::OnPreExit.AddRaw(this, &FMyEditorModule::DestroyEditorData);
}

void FMyEditorModule::ShutdownModule()
{
// #if WITH_EDITOR
// 	ULogicData::DestroyEditorLogicData();
// 	UBaseData::DestroyEditorBaseData();
// 	UResMgr::DestroyEditorResMgr();
// #endif
}


void FMyEditorModule::OnEngineLoopInitComplete()
{
	//GEngine->OnWorldAdded().AddRaw(this, &FMyEditorModule::OnWorldAdded);

	UAdminWorld::CreateEditorAdminWorld();
	//UAdminWorld* pAdminWorld = UAdminWorld::Get(nullptr);
}

void FMyEditorModule::DestroyEditorData()
{
	UAdminWorld::DestroyEditorAdminWorld();
}

IMPLEMENT_GAME_MODULE(FMyEditorModule, MyEditor);
