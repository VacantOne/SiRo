// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSingle.h"
#include "Engine/World.h"

/**
 * 在每个GameInstance内是唯一的
 */

class MYCORE_API USingleExpand
{
public:
	template<class T>
	static T* CreateSingle(UGameInstance* pGameInstance, UClass* pClass = nullptr)
	{
#if WITH_EDITOR
		UGameSingle* pSingle1 = g_pGameSingle;
		T* pSingleFind = g_pGameSingle->GetGameObject<T>(pGameInstance);
		if (nullptr != pSingleFind)
		{
			// MY_LOG(LogFrame, Error, "USingleExpand::CreateSingle fail, has exist class %s", *T::StaticClass()->GetName());
			return nullptr;
		}
#endif
		T* pSingle = nullptr;
		if (nullptr == pClass)
		{
			pSingle = NewObject<T>(pGameInstance);
		}
		else
		{
			pSingle = NewObject<T>(pGameInstance, pClass);
		}
		g_pGameSingle->AddGameObject(pGameInstance, pSingle);
		return pSingle;
	}

	template<class T>
	static T* CreateSingleIfNoExist(UGameInstance* pGameInstance, UClass* pClass = nullptr)
	{
		T* pSingleFind = g_pGameSingle->GetGameObject<T>(pGameInstance);
		if (nullptr != pSingleFind)
		{
			return pSingleFind;
		}
		T* pSingle = nullptr;
		if (nullptr == pClass)
		{
			pSingle = NewObject<T>(pGameInstance);
		}
		else
		{
			pSingle = NewObject<T>(pGameInstance, pClass);
		}
		g_pGameSingle->AddGameObject(pGameInstance, pSingle);
		return pSingle;
	}

	template<class T>
	static void DeleteSingleIfExist(UGameInstance* pGameInstance)
	{
		T* pSingle = g_pGameSingle->GetGameObject<T>(pGameInstance);
		if (nullptr == pSingle)
		{
			return;
		}
		g_pGameSingle->DelGameObject(pGameInstance, pSingle);
	}

	template<class T>
	static T* Get(UWorld* pWorld)
	{
		return g_pGameSingle->GetGameObject<T>(pWorld->GetGameInstance());
	}

};
