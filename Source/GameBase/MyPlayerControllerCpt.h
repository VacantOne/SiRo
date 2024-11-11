// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCore/MyActorCpt.h"
#include "MyPlayerControllerCpt.generated.h"

/**
 *
 */
UCLASS()
class GAMEBASE_API UMyPlayerControllerCpt : public UMyActorCpt
{
	GENERATED_BODY()
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPossessPawnChange, UMyPlayerControllerCpt*);
	FOnPossessPawnChange OnControlPawnChange;

};

