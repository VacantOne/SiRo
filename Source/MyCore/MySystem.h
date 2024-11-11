// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdminWorld.h"
#include "MySystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYCORE_API UMySystem : public UObject
{
	GENERATED_BODY()
public:
	template<typename TSys>
	static TSys* CreateSystem(UAdminWorld* pAdminWorld)
	{
#if WITH_EDITOR
		if (!pAdminWorld->CheckCanAddSystem(TSys::StaticClass()))
			return nullptr;
#endif
		UWorld* pWorld = pAdminWorld->GetWorld();
		TSys* pSystem = nullptr;
		if (nullptr != pWorld)
		{
			//pSystem = NewObject<TSys>(pWorld->GetGameInstance());
			pSystem = NewObject<TSys>(pWorld);
			//pSystem = NewObject<TSys>();
		}
		else
		{
			pSystem = NewObject<TSys>(pAdminWorld);
		}
		pAdminWorld->AddSystem(pSystem);
		return pSystem;
	}

	virtual void NativeInitSystem() {}

	UFUNCTION(BlueprintImplementableEvent)
	void InitSystem();
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Tick(float DeltaSeconds);

	virtual void NativeTick(float DeltaSeconds) {}

	template<typename Cpt>
	FORCEINLINE FCptNativeDeclare& QueryCptInitialize()
	{
		return UAdminWorld::Get(GetWorld())->QueryCptInitialize<Cpt>();
	}

	//系统监听组件的Initialize，增加委托
	UFUNCTION(BlueprintCallable)
	void CptInitializeAdd(UClass *pClass, const FCptDelegate& InDelegate)
	{
		UAdminWorld::Get(GetWorld())->QueryCptInitialize(pClass).Add(InDelegate);
	}

	template<typename Cpt>
	FORCEINLINE FCptNativeDeclare& QueryCptBeginPlay()
	{
		UWorld* pWorld = GetWorld();
		return UAdminWorld::Get(pWorld)->QueryCptBeginPlay<Cpt>();
	}

	//系统监听组件的BeginPlay，增加委托
	UFUNCTION(BlueprintCallable)
	void CptBeginPlayAdd(UClass *pClass, const FCptDelegate& InDelegate)
	{
		UAdminWorld::Get(GetWorld())->QueryCptBeginPlay(pClass).Add(InDelegate);
	}

	template<typename Cpt>
	FORCEINLINE FCptNativeDeclare& QueryCptEndPlay()
	{
		return UAdminWorld::Get(GetWorld())->QueryCptEndPlay<Cpt>();
	}

	//系统监听组件的EndPlay，增加委托
	UFUNCTION(BlueprintCallable)
		void CptEndPlayAdd(UClass *pClass, const FCptDelegate& InDelegate)
	{
		UAdminWorld::Get(GetWorld())->QueryCptEndPlay(pClass).Add(InDelegate);
	}

	FORCEINLINE FMsgDeclare& QueryMsgProcess(unsigned short usMsgType)
	{
		return UAdminWorld::Get(GetWorld())->QueryMsgProcess(usMsgType);
	}

// 	FORCEINLINE float GetTickDelta() const { return m_fCurrentTick; }
// 
// 	FORCEINLINE float GetTickInterval() const {return m_fTickInterval; }
public:
	void TickCheck(float DeltaSeconds);
	void SetTickInterval(float fTickInterval);
	int m_nTickPriority;

private:
	float m_fTickInterval;
	float m_fCurrentTick;
};
