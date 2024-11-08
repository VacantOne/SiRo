// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCore/ModuleInstance.h"
#include "GameSystemInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMESYSTEM_API UGameSystemInstance : public UObject, public IModuleInstance
{
	GENERATED_BODY()
protected:
	virtual void InitInstance(UGameInstance* pGameInstance) override;
	virtual void ShutdownInstance(bool bCanDelGlobalObject) override;
};
