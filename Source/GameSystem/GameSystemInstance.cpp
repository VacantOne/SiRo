// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSystemInstance.h" 
#include "MyCore/MySystem.h"
#include "MyCore/AdminWorld.h"
#include "CrushGameSystem.h"
//#include "Engine/GameInstance.h"

void UGameSystemInstance::InitInstance(UGameInstance* pGameInstance)
{
	//UWorld* pWorld = pGameInstance->GetWorld();
	UWorld* pWorld = GetWorld();

	if (pWorld != nullptr)
	{
		UAdminWorld* pAdminWorld = UAdminWorld::Get(pWorld);

		if (pAdminWorld != nullptr)
		{
			//UMySystem::CreateSystem<UCrushGameSystem>(pAdminWorld.Get());
			UMySystem::CreateSystem<UCrushGameSystem>(pAdminWorld);

		}
	}
}

void UGameSystemInstance::ShutdownInstance(bool bCanDelGlobalObject)
{
}