// Fill out your copyright notice in the Description page of Project Settings.


#include "GameComponentInstance.h"
// #include "GameBattleSingleAttr.h"
// #include "LogicData.h"
// #include "SingleAttr.h"
// #include "Engine/GameInstance.h"
// #include "LoginSingleAttr.h"
// #include "ClientJoystickSingleAttr.h"

// #include "GameSwitchMapAttr.h"
// #include "InputCacheMgr.h"
// #include "SelectTargetMgr.h"
// #include "GamepadSingleAttr.h"
// #include "PreloadResourceManager.h"
// #include <CameraUserSettingMgr.h>

void UGameComponentInstance::InitInstance(UGameInstance* pGameInstance)
{
	// ULogicData::CreateGameLogicDataIfNull();
	// USingleAttr::CreateSingleAttrIfNoExist<UGameBattleSingleAttr>(pGameInstance);
	// USingleAttr::CreateSingleAttrIfNoExist<ULoginSingleAttr>(pGameInstance);
	// USingleAttr::CreateSingleAttrIfNoExist<UClientJoystickSingleAttr>(pGameInstance);
	// USingleAttr::CreateSingleAttrIfNoExist<UGameSwitchMapAttr>(pGameInstance);
	// USingleAttr::CreateSingleAttrIfNoExist<USelectTargetMgr>(pGameInstance);
	// USingleAttr::CreateSingleAttrIfNoExist<UInputCacheMgr>(pGameInstance);
	// USingleAttr::CreateSingleAttrIfNoExist<UGamepadSingleAttr>(pGameInstance);
	// USingleAttr::CreateSingleAttrIfNoExist<UPreloadResourceManager>(pGameInstance);
	// USingleAttr::CreateSingleAttrIfNoExist<UCameraUserSettingMgr>(pGameInstance);
}

void UGameComponentInstance::ShutdownInstance(bool bCanDelGlobalObject)
{
	// if (bCanDelGlobalObject)
	// {
	// 	ULogicData::DestroyGameLogicData();
	// 	USingleAttr::DeleteSingleAttrIfExist<UGameBattleSingleAttr>(GetWorld()->GetGameInstance());
	// 	USingleAttr::DeleteSingleAttrIfExist<ULoginSingleAttr>(GetWorld()->GetGameInstance());
	// 	USingleAttr::DeleteSingleAttrIfExist<UClientJoystickSingleAttr>(GetWorld()->GetGameInstance());
	// 	USingleAttr::DeleteSingleAttrIfExist<UGameSwitchMapAttr>(GetWorld()->GetGameInstance());
	// 	USingleAttr::DeleteSingleAttrIfExist<USelectTargetMgr>(GetWorld()->GetGameInstance());
	// 	USingleAttr::DeleteSingleAttrIfExist<UInputCacheMgr>(GetWorld()->GetGameInstance());
	// 	USingleAttr::DeleteSingleAttrIfExist<UGamepadSingleAttr>(GetWorld()->GetGameInstance());
	// 	USingleAttr::DeleteSingleAttrIfExist<UPreloadResourceManager>(GetWorld()->GetGameInstance());
	// 	USingleAttr::DeleteSingleAttrIfExist<UCameraUserSettingMgr>(GetWorld()->GetGameInstance());
	// }
}
