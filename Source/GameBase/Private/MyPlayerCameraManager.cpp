#include "MyPlayerCameraManager.h"
#include "Camera/CameraActor.h"

AMyPlayerCameraManager::AMyPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ViewPitchMin = -75.f; //从上往下看
	ViewPitchMax = 50.f; //从底部往上看
}

void AMyPlayerCameraManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//创建的默认相机并没有什么作用
	if (AnimCameraActor)
	{
		AnimCameraActor->Destroy();
		AnimCameraActor->SetOwner(nullptr);
		AnimCameraActor = nullptr;
	}
}
