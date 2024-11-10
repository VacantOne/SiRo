// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameSingle.generated.h"

class UGameInstance;
//配置在项目设置里，游戏模式下启动的时候会被构造
//编辑器模式下启动的时候就会被构造,进入游戏后不会再构造
//游戏业务层不使用该类
/**
 * 
 */
UCLASS(BlueprintType)
class MYCORE_API UGameSingle : public UObject
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable)
		static UGameSingle* Get();
	//UFUNCTION(BlueprintCallable)
	//static TUniquePtr<UGameSingle>& Get();


	//游戏业务层不允许使用
	void AddGameObject(UGameInstance* pGameInstance, UObject* pObject);
	void DelGameObject(UGameInstance* pGameInstance, UObject* pObject);
	void ClearGameObject(UGameInstance* pGameInstance);

	//只有资源管理器之类的真正的全局对象使用
	void AddSingleObject(UObject* pObject);
	void DelSingleObject(UObject* pObject);

	template<class T> 
	T* GetSingleObject()
	{
		for (UObject* pObject : m_arrayGameObject)
		{
			T* pT = Cast<T>(pObject);
			if (nullptr != pT)
			{
				return pT;
			}
		}
		return nullptr;
	}

	template<class T>
	T* GetGameObject(UGameInstance* pGameInstance)
	{
		TArray<TWeakObjectPtr<UObject>> arrayObject;
		m_multiMapGameObject.MultiFind(pGameInstance, arrayObject);
		for (TWeakObjectPtr<UObject> pObject : arrayObject)
		{
			T* pT = Cast<T>(pObject.Get());
			if (nullptr != pT)
			{
				return pT;
			}
		}
		return nullptr;
	}

	template<class T>
	void DelGameObject(UGameInstance* pGameInstance)
	{
		TArray<TWeakObjectPtr<UObject>> arrayObject;
		m_multiMapGameObject.MultiFind(pGameInstance, arrayObject);
		for (TWeakObjectPtr<UObject> pObject : arrayObject)
		{
			T* pT = Cast<T>(pObject.Get());
			if (nullptr != pT)
			{
				DelGameObject(pGameInstance, pObject.Get());
				return;
			}
		}
	}

	//用在编辑器下客户端多份实例的时候需要传名字
	template<class T>
	T* GetGameObjectByName(UGameInstance* pGameInstance, const FName& name)
	{
		TArray<TWeakObjectPtr<UObject>> arrayObject;
		m_multiMapGameObject.MultiFind(pGameInstance, arrayObject);
		for (TWeakObjectPtr<UObject> pObject : arrayObject)
		{
			if (!pObject.IsValid())
			{
				continue;
			}

			if (pObject->GetName() == name.ToString())
			{
				T* pT = Cast<T>(pObject.Get());
				if (nullptr != pT)
				{
					return pT;
				}
			}
		}
		return nullptr;
	}

	template<class T>
	void DelGameObjectByName(UGameInstance* pGameInstance, const FName& name)
	{
		TArray<TWeakObjectPtr<UObject>> arrayObject;
		m_multiMapGameObject.MultiFind(pGameInstance, arrayObject);
		for (TWeakObjectPtr<UObject> pObject : arrayObject)
		{
			if (!pObject.IsValid())
			{
				continue;
			}

			if (pObject->GetName() == name.ToString())
			{
				T* pT = Cast<T>(pObject.Get());
				if (nullptr != pT)
				{
					DelGameObject(pGameInstance, pObject.Get());
					return;
				}
			}
		}
	}

	UFUNCTION(BlueprintCallable)
		UObject* GetGameObject(UGameInstance* pGameInstance, UClass* pClass);

private:
	TMultiMap<UGameInstance*, TWeakObjectPtr<UObject>> m_multiMapGameObject;
	UPROPERTY(Transient)
		TArray<TObjectPtr<UObject>> m_arrayGameObject;
};

#define g_pGameSingle (UGameSingle::Get())
