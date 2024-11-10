#include "GameSingle.h"
#include "Engine/Engine.h"

//TUniquePtr<UGameSingle>& UGameSingle::Get()
//{
//	static TUniquePtr<UGameSingle> instance = []() -> TUniquePtr<UGameSingle> {
//		//auto a = NewObject<UAdminWorld>(pWorld->GetGameInstance());
//		return TUniquePtr<UGameSingle>(NewObject<UGameSingle>(GEngine));
//		}();
//	return instance;
//}

UGameSingle* UGameSingle::Get()
{
#if WITH_EDITOR
	return Cast<UGameSingle>(GEngine->GameSingleton);
#else
	static UGameSingle* s_pGameSingle = Cast<UGameSingle>(GEngine->GameSingleton);
	return s_pGameSingle;
#endif
}

void UGameSingle::AddGameObject(UGameInstance* pGameInstance, UObject* pObject)
{
	m_multiMapGameObject.Add(pGameInstance, pObject);
	m_arrayGameObject.Add(pObject);
}
void UGameSingle::DelGameObject(UGameInstance* pGameInstance, UObject* pObject)
{
	m_multiMapGameObject.Remove(pGameInstance, pObject);
	m_arrayGameObject.RemoveSingle(pObject);
}

UObject* UGameSingle::GetGameObject(UGameInstance* pGameInstance, UClass* pClass)
{
	if (nullptr == pClass)
	{
		// MY_LOG_ERROR("UGameSingle::GetGameObject(UGameInstance* pGameInstance, UClass* pClass) fail, pClass==null");
		return nullptr;
	}

	TArray<TWeakObjectPtr<UObject>> arrayObject;
	m_multiMapGameObject.MultiFind(pGameInstance, arrayObject);
	for (TWeakObjectPtr<UObject> pObject : arrayObject)
	{
		if (!pObject.IsValid())
		{
			continue;
		}

		if (pObject->IsA(pClass))
		{
			return pObject.Get();
		}
	}
	return nullptr;
}

void UGameSingle::ClearGameObject(UGameInstance* pGameInstance)
{
	TArray<TWeakObjectPtr<UObject>> arrayObject;
	m_multiMapGameObject.MultiFind(pGameInstance, arrayObject);
	for (TWeakObjectPtr<UObject> pObject : arrayObject)
	{
		if (!pObject.IsValid())
		{
			continue;
		}
		m_arrayGameObject.RemoveSingle(pObject.Get());
	}
	m_multiMapGameObject.Remove(pGameInstance);
}

void UGameSingle::AddSingleObject(UObject* pObject)
{
	m_arrayGameObject.Add(pObject);
}
void UGameSingle::DelSingleObject(UObject* pObject)
{
	m_arrayGameObject.RemoveSingle(pObject);
}
