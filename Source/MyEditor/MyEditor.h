// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Modules/ModuleInterface.h"
#include "Engine/World.h"

class FMyEditorModule : public IModuleInterface
{
protected:
	virtual void StartupModule() override;
 	virtual void ShutdownModule() override;
	
private:

	void OnEngineLoopInitComplete();
	void DestroyEditorData();
};
