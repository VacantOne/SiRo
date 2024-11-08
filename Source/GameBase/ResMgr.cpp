#include "ResMgr.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"

#if WITH_EDITOR
#include "Settings/ProjectPackagingSettings.h"
#endif

UResMgr* g_pGameResMgr = nullptr;
#if WITH_EDITOR
UResMgr* g_pEditorResMgr = nullptr;
#endif

UResMgr* UResMgr::Get(UWorld* pWorld)
{
#if WITH_EDITOR
	if (nullptr == pWorld)
	{
		if (nullptr != g_pGameResMgr)
			return g_pGameResMgr;
		if (nullptr == g_pEditorResMgr)
			CreateEditorResMgr();
		return g_pEditorResMgr;
	}
	else
	{
		if (pWorld->IsGameWorld())
		{
			return g_pGameResMgr;
		}
		else
		{
			if (nullptr == g_pEditorResMgr)
				CreateEditorResMgr();
			return g_pEditorResMgr;
		}
	}
#else
	return g_pGameResMgr;
#endif
}


void UResMgr::CreateGameResMgrIfNull(UGameInstance* pGameInstance)
{
	if (nullptr == g_pGameResMgr)
	{
		g_pGameResMgr = NewObject<UResMgr>(pGameInstance);
		g_pGameResMgr->AddToRoot();
	}
}
void UResMgr::DestroyGameResMgr()
{
	if (nullptr != g_pGameResMgr)
	{
		g_pGameResMgr->RemoveFromRoot();
		g_pGameResMgr = nullptr;
	}
}

#if WITH_EDITOR
void UResMgr::CreateEditorResMgr()
{
	if (nullptr == g_pEditorResMgr)
	{
		g_pEditorResMgr = NewObject<UResMgr>();
		g_pEditorResMgr->AddToRoot();
	}
}


void UResMgr::DestroyEditorResMgr()
{
	if (nullptr == g_pEditorResMgr)
	{
		g_pEditorResMgr->RemoveFromRoot();
		g_pEditorResMgr = nullptr;
	}
}

bool UResMgr::CheckResPath(const FString& path)
{
	if (path.IsEmpty())
	{
		return false;
	}

	const UProjectPackagingSettings* PackagingSettings = GetDefault<UProjectPackagingSettings>();
	if (nullptr == PackagingSettings)
	{
		return false;
	}
	bool bIsAlwaysCookDirectory = false;
	for (const FDirectoryPath& dirPath : PackagingSettings->DirectoriesToAlwaysCook)
	{
		if (path.Contains(dirPath.Path))
		{
			bIsAlwaysCookDirectory = true;
			break;
		}
	}
	if (!bIsAlwaysCookDirectory)
	{
		if (path.Contains("/Engine/"))
		{
			return true;
		}
		//MY_LOG(LogAssetLoad, Error, "UResMgr::CheckResPath error, 为保证资源能正常cook请将 %s 资源挪到始终cook的目录, 否则发布版会丢失该资源 \n", *path);
		return false;
	}

	return true;
}


#endif
