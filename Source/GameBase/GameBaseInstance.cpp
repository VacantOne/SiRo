#include "GameBaseInstance.h"
// #include "ResMgr.h"
#include "MyCore/AdminWorld.h"
// #include "BaseData.h"
#include "Engine/GameInstance.h"
// #include "MyGameUserSetting.h"

void UGameBaseInstance::InitInstance(UGameInstance* pGameInstance)
{
	// UResMgr::CreateGameResMgrIfNull(pGameInstance);
  	// UBaseData::CreateGameBaseDataIfNull(pGameInstance);
	// UMyGameUserSetting::Get()->UpdateScreenPercentage();

	//TUniquePtr<UAdminWorld>& pAdminWorld = UAdminWorld::Get(pGameInstance->GetWorld());
	UAdminWorld* pAdminWorld = UAdminWorld::Get(pGameInstance->GetWorld());
	m_handleAdminWorldTick = FWorldDelegates::OnWorldPostActorTick.AddUObject(pAdminWorld, &UAdminWorld::TickAdminWorld);
}

void UGameBaseInstance::ShutdownInstance(bool bCanDelGlobalObject)
{
	FWorldDelegates::OnWorldPostActorTick.Remove(m_handleAdminWorldTick);
	m_handleAdminWorldTick.Reset();
	//UAdminWorld::Get(GetWorld()).Reset();
	if (bCanDelGlobalObject)
	{
		// UBaseData::DestroyGameBaseData();
 		// UResMgr::DestroyGameResMgr();
	}
}
