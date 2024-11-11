// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCore/ModuleInstance.h"
#include "GameComponentInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMECOMPONENT_API UGameComponentInstance : public UObject, public IModuleInstance
{
	GENERATED_BODY()
	
public:
	virtual void InitInstance(UGameInstance* pGameInstance) override;
	virtual void ShutdownInstance(bool bCanDelGlobalObject) override;
};
