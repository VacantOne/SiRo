// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
// #include "EntityWrapper.h"
#include "MyGameMode.generated.h"


UCLASS()
class AMyGameMode : public AGameModeBase// , public IEntityWrapper
{
	GENERATED_UCLASS_BODY()

private:

	virtual void PreInitializeComponents() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
 	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;

	UClass* WidgetClass;
};
