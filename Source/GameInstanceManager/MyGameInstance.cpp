#include "MyGameInstance.h"
// #include "GameSingle.h"
#include "Engine/Engine.h"
//#include "MyCore/SingleExpand.h"
// #include "AdminWorld.h"
#include "MyCore/ModuleInstance.h"
// #include "GameBaseInstance.h"
#include "GameSystem/GameSystemInstance.h"
// #include "ResMgr.h"
// #include "LuaGameInstance.h"
// #include "MyShellInstance.h"
// #include "GameComponentInstance.h"


UMyGameInstance::FOnMyGameInstanceInit UMyGameInstance::OnMyGameInstanceInit;
// FDelegateHandle UMyGameInstance::OnTevatLoggerHandle;

void UMyGameInstance::Init()
{
	
// 	UCoreExpand::CreateMyNeedDir();
	Super::Init();
	OnMyGameInstanceInit.Broadcast(this);

	UGameSystemInstance* pGameSystemInstance = NewObject<UGameSystemInstance>();
	 m_arrayModuleInstance.Add(pGameSystemInstance);
	
	for (auto instance : m_arrayModuleInstance)
	{
		IModuleInstance* pModuleInstance = dynamic_cast<IModuleInstance*>(instance.Get());
		pModuleInstance->InitInstance(this);
	}
}


void UMyGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
	InnerStartGameInstance();
}


void UMyGameInstance::InnerStartGameInstance()
{
	for (auto instance : m_arrayModuleInstance)
	{
		if (!instance.IsValid())
		{
			continue;
		}
		IModuleInstance* pModuleInstance = dynamic_cast<IModuleInstance*>(instance.Get());
		pModuleInstance->StartInstance(this);
	}
}

void UMyGameInstance::Shutdown()
{
	bool bCanDelGlobalObject = false;
	int32 PIEInstance = GetWorldContext() ? GetWorldContext()->PIEInstance : -1;
	if (PIEInstance <= 0)
	{	//多个PIE客户端共有的，在最后一个结束时候删
		bCanDelGlobalObject = true;
	}

	for (int i = m_arrayModuleInstance.Num() - 1; i >= 0; i--)
	{
		if (!m_arrayModuleInstance[i].IsValid())
		{
			continue;
		}
		IModuleInstance* pModuleInstance = dynamic_cast<IModuleInstance*>(m_arrayModuleInstance[i].Get());
		pModuleInstance->ShutdownInstance(bCanDelGlobalObject);
	}
	m_arrayModuleInstance.Empty();

	Super::Shutdown();
}
