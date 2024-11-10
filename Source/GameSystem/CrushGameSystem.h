#pragma once
#include "MyCore/MySystem.h"
#include "CrushGameSystem.generated.h"

UCLASS()
class UCrushGameSystem : public UMySystem
{
	GENERATED_BODY()
public:
	UCrushGameSystem()
	{
		//UE_LOG(LogTemp, Warning, TEXT(" ============ UCrushGameSystem"));
	}
	virtual void NativeTick(float DeltaSeconds) override
	{
		//UE_LOG(LogTemp, Warning, TEXT(" ============ UCrushGameSystem"));
	}
};
