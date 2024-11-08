// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "ParamStream.h"
#include "Engine/StreamableManager.h"
#include "ResMgr.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class GAMEBASE_API UResMgr : public UObject
{
	GENERATED_BODY()
private:
	//目前查找字体会无法转换成UFont, 查找字体目前用的ConstructorHelpersInternal::FindOrLoadObject<UFont>(fontName);
public:
	UFUNCTION(BlueprintPure)
		static UResMgr* Get(UWorld* pWorld = nullptr);

	//同步加载资源
	//strPathFileName：指定路径
	//返回值：加载好的UClass资源
	UFUNCTION(BlueprintPure)
		FORCEINLINE UClass* LoadSynchronousClass(const FString& strPathFileName)
	{
		return LoadSynchronous<UClass>(strPathFileName);
	}

	FORCEINLINE UClass* LoadSynchronousClass(const FSoftClassPath& strPathFileName)
	{
		return LoadSynchronous<UClass>(strPathFileName);
	}

	UFUNCTION(BlueprintPure)
	FORCEINLINE UObject* LoadSynchronousObject(const FSoftObjectPath& strPathFileName)
	{
		return LoadSynchronous<UObject>(strPathFileName);
	}

	//同步加载资源
	template<typename T>
	T* LoadSynchronous(const FSoftObjectPath& path)
	{
#if WITH_EDITOR
		bool bRet = CheckResPath(path.GetAssetPathString());
		if (bRet == false)
		{
			return nullptr;
		}
#endif
		UObject* pObj = m_streamableManager.LoadSynchronous(path);
		if (nullptr == pObj)
		{
			//MY_LOG(LogAssetLoad, Warning, "UResMgr::LoadSynchronous , Class=%s, Name=%s", *T::StaticClass()->GetName(), *path.ToString());
			return nullptr;
		}
		T* pT = Cast<T>(pObj);
		if (nullptr == pT)
		{
			//MY_LOG_WARNING("UResMgr::LoadObject Cast fail, Class=%s, Name=%s", *T::StaticClass()->GetName(), *path.ToString());
			return nullptr;
		}

		return pT;
	}
	//同步加载资源
	template<typename T>
	FORCEINLINE T* LoadSynchronous(const FString& strPathFileName)
	{
		FSoftObjectPath path(strPathFileName);
		return LoadSynchronous<T>(path);
	}

	//异步加载资源
	FORCEINLINE TSharedPtr<FStreamableHandle> LoadAsynchronous(const FSoftObjectPath& path, const FStreamableDelegate& DelegateToCall,int32 Priority)
	{
#if WITH_EDITOR
		bool bRet = CheckResPath(path.GetAssetPathString());
		if (bRet == false)
		{
			return nullptr;
		}
#endif
		return m_streamableManager.RequestAsyncLoad(path, DelegateToCall,Priority);
	}

	//异步加载资源
	FORCEINLINE_DEBUGGABLE TSharedPtr<FStreamableHandle> 
	LoadAsynchronous(const TArray<FSoftObjectPath>& paths, const FStreamableDelegate& DelegateToCall,int32 Priority)
	{
#if WITH_EDITOR
		for (const FSoftObjectPath& path : paths)
		{
			bool bRet = CheckResPath(path.GetAssetPathString());
			if (bRet == false)
			{
				return nullptr;
			}
		}
#endif
		return m_streamableManager.RequestAsyncLoad(paths, DelegateToCall, Priority);
	}

	static void CreateGameResMgrIfNull(class UGameInstance* pGameInstance);
	static void DestroyGameResMgr();
#if WITH_EDITOR
	static void CreateEditorResMgr();
	static void DestroyEditorResMgr();
#endif
private:
#if WITH_EDITOR
	bool CheckResPath(const FString& path);
#endif
	FStreamableManager m_streamableManager;
};

#define g_pResMgr (UResMgr::Get())