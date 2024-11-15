#include "CrushGameSystem.h"
#include "GameBase/MyPlayerControllerCpt.h"

void UCrushGameSystem::NativeInitSystem()
{
    QueryCptBeginPlay<UMyPlayerControllerCpt>().AddUObject(this, &ThisClass::OnPlayerControllerCptBeginPlay);
}

void UCrushGameSystem::OnPlayerControllerCptBeginPlay(UActorComponent* pActorCpt)
{

}

void UCrushGameSystem::NativeTick(float DeltaSeconds)
{
    Super::NativeTick(DeltaSeconds);
}