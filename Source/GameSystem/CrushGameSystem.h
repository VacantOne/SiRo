#pragma once
#include "MyCore/MySystem.h"
#include "CrushGameSystem.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UCrushGameSystem : public UMySystem
{
	GENERATED_BODY()
public:
	virtual void NativeInitSystem() override;
	void OnPlayerControllerCptBeginPlay(UActorComponent* pActorCpt);
protected:
	virtual void NativeTick(float DeltaSeconds) override;
};
