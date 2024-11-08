// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGameSystem : public IModuleInterface
{
public:
    // IModuleInterface 接口方法
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};