// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AdminWorld.h"
#include "ComponentWrapper.generated.h"


UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UComponentWrapper : public UInterface {
	GENERATED_BODY()
};

class MYCORE_API IComponentWrapper {

	GENERATED_IINTERFACE_BODY()
public:

	virtual void AssignComponent(UAdminWorld* pAdminWorld, uint32 idEntity) {}
	virtual void RemoveComponent(UAdminWorld* pAdminWorld, uint32 idEntity) {}
};
