#include "AdminWorld.h"
 #include "SingleExpand.h"
// #include "TimerManager.h"
#include "MySystem.h"
#include "GameFramework/WorldSettings.h"
#include "Engine/GameInstance.h"
// #include "MyActorCpt.h"

// const int MAX_GET_CPLUS_CLASS_COUNT = 5;

#if WITH_EDITOR
UAdminWorld* g_pEditorAdminWorld = nullptr;
#endif

UAdminWorld::UAdminWorld()
{
//  	m_pRealTimerManager = MakeShareable(new FTimerManager(nullptr, true));
 	// m_pTi merManager = MakeShareable(new FTimerManager());
}

 UAdminWorld* UAdminWorld::Get(UWorld* pWorld)
 {
 	if (nullptr != pWorld)
 	{
 		// UAdminWorld* pAdminWorld = USingleExpand::Get<UAdminWorld>(pWorld);
 		UAdminWorld* pAdminWorld = USingleExpand::Get<UAdminWorld>(pWorld);
 		if (nullptr != pAdminWorld)
 			return pAdminWorld;
 	}
 #if WITH_EDITOR
 	return g_pEditorAdminWorld;
 #else
 	return nullptr;
 #endif
 }

// uint32 UAdminWorld::CreateEntity()
// {
// 	return m_registry.create();
// }

// void UAdminWorld::DestroyEntity(uint32 idEntity)
// {
// 	m_registry.destroy(idEntity);
// }

// UClass* UAdminWorld::GetActorComponentClass(UActorComponent* pActorComponent)
// {
// 	UClass* pClass = pActorComponent->GetClass();
// 	int index = 0;
// 	for (index = 0; index < MAX_GET_CPLUS_CLASS_COUNT; ++index)
// 	{
// 		if (nullptr == pClass)
// 			break;
// 		//IsInBlueprint在独立服务端下无法判断蓝图类, 因为独立服务端/客户端下ClassGeneratedBy是nullptr, 编辑器模式下是有值的, 所以改成了只判断CLASS_CompiledFromBlueprint
// 		if (!pClass->HasAnyClassFlags(CLASS_CompiledFromBlueprint))
// 			break;

// 		UClass* pClassSuper = pClass->GetSuperClass();
// 		if (nullptr != pClassSuper && pClassSuper == UMyActorCpt::StaticClass())
// 		{
// 			//支持Lua的蓝图继承UMyActorCpt
// 			break;
// 		}
// 		pClass = pClassSuper;
// 	}

// 	if (MAX_GET_CPLUS_CLASS_COUNT == index
// 		|| nullptr == pClass)
// 	{
// 		FString strClassName = (nullptr != pClass) ? pClass->GetName() : STRING_EMPTY;
// 		MY_LOG(LogFrame, Warning, "UAdminWorld::GetActorComponentClass Class %s is of BlueprintClass", *strClassName);
// 	}
// 	return pClass;
// }

// void UAdminWorld::BroadcastActorCptInitialize(UActorComponent* pActorComponent)
// {
// 	UClass* pClass = GetActorComponentClass(pActorComponent);
// 	if (nullptr == pClass)
// 		return;
// 	FCptNativeDeclare* pCptNativeInitialize = m_mapCptNativeInitialize.Find(pClass);
// 	if (nullptr != pCptNativeInitialize)
// 	{
// 		pCptNativeInitialize->Broadcast(pActorComponent);
// 	}

// 	FCptDeclare* pCptDeclare = m_mapCptInitialize.Find(pClass);
// 	if (nullptr != pCptDeclare)
// 	{
// 		pCptDeclare->Broadcast(pActorComponent);
// 	}
// }

// void UAdminWorld::BroadcastActorCptBeginPlay(UActorComponent* pActorComponent)
// {
// 	UClass* pClass = GetActorComponentClass(pActorComponent);
// 	if (nullptr == pClass)
// 		return;
// 	FCptNativeDeclare* pCptNativeBeginPlay = m_mapCptNativeBeginPlay.Find(pClass);
// 	if (nullptr != pCptNativeBeginPlay)
// 	{
// 		pCptNativeBeginPlay->Broadcast(pActorComponent);
// 	}

// 	FCptDeclare* pCptDeclare = m_mapCptBeginPlay.Find(pClass);
// 	if (nullptr != pCptDeclare)
// 	{
// 		pCptDeclare->Broadcast(pActorComponent);
// 	}
// }

// void UAdminWorld::BroadcastActorCptEndPlay(UActorComponent* pActorComponent)
// {
// 	UClass* pClass = GetActorComponentClass(pActorComponent);
// 	if (nullptr == pClass)
// 		return;
// 	FCptNativeDeclare* pCptNativeEndPlay = m_mapCptNativeEndPlay.Find(pClass);
// 	if (nullptr != pCptNativeEndPlay)
// 	{
// 		pCptNativeEndPlay->Broadcast(pActorComponent);
// 	}

// 	FCptDeclare* pCptDeclare = m_mapCptEndPlay.Find(pClass);
// 	if (nullptr != pCptDeclare)
// 	{
// 		pCptDeclare->Broadcast(pActorComponent);
// 	}
// }

// void UAdminWorld::BroadcastMsgProcess(unsigned short usMsgType, void* pMsgInfo)
// {
// 	FMsgDeclare* pMsgDeclare = m_mapMsgProcess.Find(usMsgType);
// 	if (nullptr != pMsgDeclare)
// 	{
// 		pMsgDeclare->Broadcast(pMsgInfo);
// 	}
// }

bool UAdminWorld::CheckCanAddSystem(UClass* pClass)
{
	for (int i = m_arraySystem.Num() - 1; i >= 0; i--)
	{
		UMySystem* pMySystem = m_arraySystem[i];
		if (pMySystem->IsA(pClass))
		{
			//MY_LOG(LogFrame, Error, "CreateSystem error, System %s has exist", *pMySystem->GetClass()->GetName());
			return false;
		}
	}
	return true;
}

void UAdminWorld::AddSystem(UMySystem* pSystem)
{
	pSystem->NativeInitSystem();
	pSystem->InitSystem();
	m_arraySystem.Add(pSystem);
}

UMySystem* UAdminWorld::CreateSystem(UClass* pClass)
{
	if (nullptr == pClass)
	{
		// MY_LOG(LogFrame, Error, "UAdminWorld::CreateSystem error, pClass = null!");
		return nullptr;
	}
#if WITH_EDITOR
	if (!CheckCanAddSystem(pClass))
		return nullptr;
#endif

	UMySystem* pSystem = NewObject<UMySystem>(GetWorld()->GetGameInstance(), pClass);
	//UMySystem* pSystem = nullptr;
	AddSystem(pSystem);
	return pSystem;
}


void UAdminWorld::TickAdminWorld(UWorld* pWorld, ELevelTick eTickType, float DeltaSeconds)
{
	// if (!MyIsValid(pWorld))
	// 	return;
	// if (pWorld != GetWorld())
	// 	return; //绑定全局的静态委托会每个World都会绑定,这里的回调会是每个 客户端/服务端 的
	// QUICK_SCOPE_CYCLE_COUNTER(STAT_MySystemTickTime);

	//真实时间tick
// 	m_pRealTimerManager->Tick();

	//受全局缩放和pause影响tick
	// float fMyDeltaSeconds = (0.f == m_fLastAudioTimeSeconds) ? pWorld->AudioTimeSeconds : pWorld->AudioTimeSeconds - m_fLastAudioTimeSeconds;
	// m_fLastAudioTimeSeconds = pWorld->AudioTimeSeconds;
	// float fScale = pWorld->GetWorldSettings()->TimeDilation;
	// m_pTimerManager->Tick(fScale * fMyDeltaSeconds * 1000);

	for (UMySystem* pSystem : m_arraySystem)
	{
		pSystem->TickCheck(DeltaSeconds);
	}
}

// void UAdminWorld::SortSystemByTickPriority()
// {
// 	m_arraySystem.Sort([](const UMySystem& A, const UMySystem& B)
// 	{
// 		return A.m_nTickPriority < B.m_nTickPriority;
// 	});
// }

#if WITH_EDITOR
void UAdminWorld::CreateEditorAdminWorld()
{
	if (nullptr == g_pEditorAdminWorld)
	{
		g_pEditorAdminWorld = NewObject<UAdminWorld>();
		g_pEditorAdminWorld->AddToRoot();
	}
}

void UAdminWorld::DestroyEditorAdminWorld()
{
	if (nullptr != g_pEditorAdminWorld)
	{
		g_pEditorAdminWorld->RemoveFromRoot();
		g_pEditorAdminWorld = nullptr;
	}
}
#endif
