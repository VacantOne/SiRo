// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
//#include "entt.hpp"
//#include "Misc/ScopeLock.h"
#include "Templates/UniquePtr.h" // 假设TUniquePtr定义在这个头文件中
#include "AdminWorld.generated.h"

// class UActorComponent;
class UMySystem;
// DECLARE_MULTICAST_DELEGATE_OneParam(FCptNativeDeclare, UActorComponent*);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCptDeclare, UActorComponent*, pActorComponent);
// DECLARE_DYNAMIC_DELEGATE_OneParam(FCptDelegate, UActorComponent*, pActorComponent);
// DECLARE_MULTICAST_DELEGATE_OneParam(FMsgDeclare, void*);

/**
 * 每个World内唯一
 */
UCLASS(Blueprintable)
class MYCORE_API UAdminWorld : public UObject
{
	GENERATED_BODY()
public:
	 UFUNCTION(BlueprintPure, Category = "--AdminWorld--")
	 static UAdminWorld* Get(UWorld* pWorld);

	//static TUniquePtr<UAdminWorld>& Get(UWorld* pWorld)
	//{
	//	static TUniquePtr<UAdminWorld> instance = [pWorld]() -> TUniquePtr<UAdminWorld> {
	//		//auto a = NewObject<UAdminWorld>(pWorld->GetGameInstance());
	//		return TUniquePtr<UAdminWorld>(NewObject<UAdminWorld>(pWorld));
	//		}();
	//	if (nullptr == instance.Get() || !instance.IsValid())
	//		instance = TUniquePtr<UAdminWorld>(NewObject<UAdminWorld>(pWorld));
	//	return instance;
	//}

	UAdminWorld();
	~UAdminWorld() {};
	uint32 CreateEntity();
	void DestroyEntity(uint32 idEntity);

	// template<typename Cpt>
	// FORCEINLINE FCptNativeDeclare& QueryCptInitialize()
	// {
	// 	return m_mapCptNativeInitialize.FindOrAdd(Cpt::StaticClass());
	// }

	// FORCEINLINE FCptDeclare& QueryCptInitialize(UClass *pClass)
	// {
	// 	return m_mapCptInitialize.FindOrAdd(pClass);
	// }

	// template<typename Cpt>
	// FORCEINLINE FCptNativeDeclare& QueryCptBeginPlay()
	// {
	// 	return m_mapCptNativeBeginPlay.FindOrAdd(Cpt::StaticClass());
	// }

	// FORCEINLINE FCptDeclare& QueryCptBeginPlay(UClass *pClass)
	// {
	// 	return m_mapCptBeginPlay.FindOrAdd(pClass);
	// }

	// template<typename Cpt>
	// FORCEINLINE FCptNativeDeclare& QueryCptEndPlay()
	// {
	// 	return m_mapCptNativeEndPlay.FindOrAdd(Cpt::StaticClass());
	// }

	// FORCEINLINE FCptDeclare& QueryCptEndPlay(UClass *pClass)
	// {
	// 	return m_mapCptEndPlay.FindOrAdd(pClass);
	// }

	// FORCEINLINE FMsgDeclare& QueryMsgProcess(unsigned short usMsgType)
	// {
	// 	return m_mapMsgProcess.FindOrAdd(usMsgType);
	// }

	// template<typename Component, typename... Args>
	// FORCEINLINE Component& AssignComponent(const uint32 entity, Args &&... args) {
	// 	return m_registry.emplace<Component>(entity, std::forward<Args>(args)...);
	// }

	// void BroadcastActorCptInitialize(UActorComponent* pActorComponent);
	// void BroadcastActorCptBeginPlay(UActorComponent* pActorComponent);
	// void BroadcastActorCptEndPlay(UActorComponent* pActorComponent);
	// void BroadcastMsgProcess(unsigned short usMsgType, void* pMsgInfo);

	// template<typename Component>
	// FORCEINLINE void RemoveComponent(uint32 entity) {
	// 	m_registry.remove<Component>(entity);
	// }

	// template<typename... Component>
	// FORCEINLINE auto ViewCpt() {
	// 	return m_registry.view<Component...>();
	// }

	bool CheckCanAddSystem(UClass* pClass);
	void AddSystem(UMySystem* pSystem);

	UFUNCTION(BlueprintCallable)
	UMySystem* CreateSystem(UClass* pClass);
	void TickAdminWorld(UWorld* pWorld, enum ELevelTick eTickType, float DeltaSeconds);
	// void SortSystemByTickPriority();

	//不受所有因素影响，只由真实时间决定的定时器
// 	TSharedPtr<class FTimerManager> m_pRealTimerManager;
 	//不受引擎游戏帧时间影响，受全局加速影响的定时器
	// TSharedPtr<class FTimerManager> m_pTimerManager;

private:
	// static UClass* GetActorComponentClass(UActorComponent* pActorComponent);
	UPROPERTY()
	TArray<TObjectPtr<UMySystem>> m_arraySystem;

	// TMap<UClass*, FCptNativeDeclare> m_mapCptNativeInitialize;
	// TMap<UClass*, FCptNativeDeclare> m_mapCptNativeBeginPlay;
	// TMap<UClass*, FCptNativeDeclare> m_mapCptNativeEndPlay;

	// //以下3个加UPROPERTY，防止Lua创建的类被GC
	// UPROPERTY()
	// 	TMap<UClass*, FCptDeclare> m_mapCptInitialize;
	// UPROPERTY()
	// 	TMap<UClass*, FCptDeclare> m_mapCptBeginPlay;
	// UPROPERTY()
	// 	TMap<UClass*, FCptDeclare> m_mapCptEndPlay;

	// TMap<unsigned short, FMsgDeclare> m_mapMsgProcess;
	// entt::basic_registry<uint32> m_registry;

	// //暂停的时候不会继续加
	// float m_fLastAudioTimeSeconds = 0.f;

#if WITH_EDITOR
public:
	static void CreateEditorAdminWorld();
	//编辑器退出的时候会自动释放全部对象，这里不需要手动释放
	static void DestroyEditorAdminWorld();
#endif
};
