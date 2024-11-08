// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSystemInstance.h"

// #include "ActorAttributeSystem.h"
// #include "AdminWorld.h"
// #include "CharacterStateSystem.h"
// #include "GameBattleSystem.h"
// #include "GameCharacterSystem.h"
// #include "GameCharacterMovementSystem.h"
// #include "Engine/GameInstance.h"
// #include "ClientJoystickSystem.h"
// #include "ClientCharacterControlSystem.h"
// #include "ClientCameraControlSystem.h"
// #include "SkillSystem.h"
// #include "RideSystem.h"
// #include "ClientMouseHoverSystem.h"
// #include "InputCacheSystem.h"
// #include "PreloadResourceSystem.h"
// #include "MapSwitchSystem.h"

void UGameSystemInstance::InitInstance(UGameInstance* pGameInstance)
{
	//UWorld* pWorld = pGameInstance->GetWorld();
	//UAdminWorld* pAdminWorld = UAdminWorld::Get(pWorld);
	UE_LOG(LogTemp, Warning, TEXT("=============== !!!!!"));
	// UMySystem::CreateSystem<UGameCharacterSystem>(pAdminWorld, 0.0001f);
\
}

void UGameSystemInstance::ShutdownInstance(bool bCanDelGlobalObject)
{
}
