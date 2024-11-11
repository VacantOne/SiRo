// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyCore/EntityWrapper.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AMyPlayerController : public APlayerController, public IEntityWrapper
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetShouldFlushKeysWhenViewportFocusChanges(bool InShouldFlush)
	{
		bShouldFlushKeysWhenViewportFocusChanges = InShouldFlush;
	}
	
	UFUNCTION(BlueprintCallable)
	bool GetShouldFlushKeysWhenViewportFocusChanges() const
	{
		return bShouldFlushKeysWhenViewportFocusChanges;
	}
	
private:
	virtual void PreInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetPawn(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual bool ShouldFlushKeysWhenViewportFocusChanges() const override;

// 	virtual void UpdateRotation(float DeltaTime) override;
private:

	class UMyPlayerControllerCpt* m_pMyPlayerControllerCpt;
	//只是用做检查是否有变化，不用来做逻辑
	TWeakObjectPtr<APawn> m_pOldControlPawn;

	// 在失焦时，是否键入次刷新Key
	bool bShouldFlushKeysWhenViewportFocusChanges : 1;
};
