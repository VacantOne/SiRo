// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ModuleInstance.generated.h"

class UGameInstance;

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UModuleInstance : public UInterface {
	GENERATED_BODY()

};

class MYCORE_API IModuleInstance {

	GENERATED_IINTERFACE_BODY()
public:
	virtual void InitInstance(UGameInstance* pGameInstance) = 0;
	virtual void StartInstance(UGameInstance* pGameInstance) {}
	virtual void ShutdownInstance(bool bCanDelGlobalObject) {}
};
