#include "MyPlayerController.h"
// #include "Engine/NetConnection.h"
#include "MyPlayerCameraManager.h"
#include "GameFramework/Pawn.h"
#include "MyPlayerControllerCpt.h"

AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	//bShowMouseCursor = true;
	PlayerCameraManagerClass = AMyPlayerCameraManager::StaticClass();
	//不从PlayerController上自动设置控制的棋子所拥有的相机。在创建相机后手动调用APlayerController::SetViewTarget
	bAutoManageActiveCameraTarget = false;
	//固定顶视角, 鼠标点击的时候返回的WorldOrigin只有2000左右;自由视角下应加大一些
 	HitResultTraceDistance = 8000;
	m_pMyPlayerControllerCpt = CreateDefaultSubobject<UMyPlayerControllerCpt>("MyPlayerControllerCpt");
}

void AMyPlayerController::SetPawn(APawn* InPawn)
{
	//不能在设置之前判断旧的Pawn, 因为客户端是通过网络复制的, 所以取不到之前的Pawn了
	//OnControlPawnChange之所以在这个地方调用是因为Possess和OnPossess只有服务器调用，而这里也能够支持客户端
	Super::SetPawn(InPawn);
	APawn* pOldControlPawn = m_pOldControlPawn.Get();
	if (pOldControlPawn != InPawn)
	{
		m_pMyPlayerControllerCpt->OnControlPawnChange.Broadcast(m_pMyPlayerControllerCpt);
		m_pOldControlPawn = InPawn;
	}
}

void AMyPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	if (APawn* pOldControlPawn = m_pOldControlPawn.Get())
	{
		m_pMyPlayerControllerCpt->OnControlPawnChange.Broadcast(m_pMyPlayerControllerCpt);
		m_pOldControlPawn.Reset();
	}
}

bool AMyPlayerController::ShouldFlushKeysWhenViewportFocusChanges() const
{
	return bShouldFlushKeysWhenViewportFocusChanges;
}

void AMyPlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	EntityCreate(GetWorld());
}

void AMyPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
// 	if (nullptr != InputComponent)
// 	{
// 		InputComponent->ClearActionBindings();
// 	}
	Super::EndPlay(EndPlayReason);
	EntityDestroy(GetWorld());
}

// void AMyPlayerController::UpdateRotation(float DeltaTime)
// {
// 	// do nothing 覆盖引擎的这个接口，在地上的时候啥也不做了
// }
