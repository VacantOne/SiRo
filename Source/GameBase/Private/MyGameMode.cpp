#include "MyGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include <Engine/Engine.h>
#include "Blueprint/UserWidget.h"

AMyGameMode::AMyGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// FSoftClassPath BpPlayerController(TEXT("/Game/Gameplay/FrameExpand/BpMyPlayerController.BpMyPlayerController_C"));
	// PlayerControllerClass = BpPlayerController.TryLoadClass<APlayerController>();
	// static ConstructorHelpers::FClassFinder<APawn> BpPawn(TEXT("/Game/Gameplay/FrameExpand/BP_Person.BP_Person_C"));
	// DefaultPawnClass = BpPawn.Class;

}

void AMyGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AMyGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	//不放到构造函数里面加载蓝图类，加载时机太早了，会导致蓝图类中项目C++中的组件数据、蓝图组件数据等丢失。
	//FSoftClassPath BpPlayerController(TEXT("/Game/Gameplay/FrameExpand/BpMyPlayerController.BpMyPlayerController_C"));
	//PlayerControllerClass = BpPlayerController.TryLoadClass<APlayerController>();
	//FSoftClassPath BpPawn(TEXT("/Game/Gameplay/FrameExpand/BP_Person.BP_Person_C"));
	//DefaultPawnClass = BpPawn.TryLoadClass<APawn>();
	Super::InitGame(MapName, Options, ErrorMessage);
}
void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
}
void AMyGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMyGameMode::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{

}