// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
// #include "EntityWrapper.h"
#include "MyPlayerCameraManager.generated.h"

UCLASS(notplaceable, BlueprintType)
class AMyPlayerCameraManager : public APlayerCameraManager//, public IEntityWrapper
{
	GENERATED_UCLASS_BODY()
protected:
	virtual void PostInitializeComponents() override;

};
