// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EntityWrapper.generated.h"

class UWorld;

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UEntityWrapper : public UInterface {
	GENERATED_BODY()

};

class MYCORE_API IEntityWrapper {

	GENERATED_IINTERFACE_BODY()
public:
	void EntityCreate(UWorld* pWorld);
	void EntityDestroy(UWorld* pWorld);
	uint32 m_idEntity; //从0开始是有效的
	uint8 m_bCreate : 1;
};
