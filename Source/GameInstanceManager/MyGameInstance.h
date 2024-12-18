// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 *
 */
UCLASS()
class GAMEINSTANCEMANAGER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;
private:
	void InnerStartGameInstance();
	TArray<TWeakObjectPtr<UObject>> m_arrayModuleInstance;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnMyGameInstanceInit, UGameInstance* /*Instance*/);
	static FOnMyGameInstanceInit OnMyGameInstanceInit;
};
