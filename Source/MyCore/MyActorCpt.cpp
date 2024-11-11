#include "MyActorCpt.h"
#include "EntityWrapper.h"
#include "Components/SceneComponent.h"
#include "AdminWorld.h"

UMyActorCpt::UMyActorCpt()
{
	bWantsInitializeComponent = true;
}

UActorComponent* UMyActorCpt::CreateCpt(AActor* pActor, UClass* pClass /*= nullptr*/)
{
	if (nullptr == pActor)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::CreateCpt error, null == pOwner");
		return nullptr;
	}

	if (nullptr == pClass)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::CreateCpt error, null == pClass");
		return nullptr;
	}

	UActorComponent* pActorComponent = NewObject<UActorComponent>(pActor, pClass);
	if (nullptr != pActorComponent)
	{
		//支持动态创建的组件显示到Details面板上
		pActor->AddInstanceComponent(pActorComponent);
		pActorComponent->RegisterComponent();
	}

	return pActorComponent;
}

void UMyActorCpt::DestroyCptByName(const FName& name)
{
	AActor* pActor = GetOwner();
	if (nullptr == pActor)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::DestroyCptByName error, null == GetOwner(), name=%s", *GetName());
		return;
	}
	const TSet<UActorComponent*>& setComponent = pActor->GetComponents();
	for (UActorComponent* pComponent : setComponent)
	{
		if (name == pComponent->GetFName())
		{
			pComponent->DestroyComponent();
			break;
		}
	}
}

UActorComponent* UMyActorCpt::GetCpt(UActorComponent* pActorComponent, UClass* pClass)
{
	if (pActorComponent == nullptr)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::GetCpt pActorComponent不合法");
		return nullptr;
	}

	if (nullptr == pClass)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::GetCpt pClass为空");
		return nullptr;
	}

	AActor* pActor = pActorComponent->GetOwner();
	if (nullptr == pActor)
	{
		// MY_LOG_ERROR("UMyScriptFunc::GetCpt pAcotr为空， 组件为%s", *pActorComponent->GetName());
		return nullptr;
	}

	return pActor->FindComponentByClass(pClass);
}

void UMyActorCpt::DestroyChildren(USceneComponent* pComponentParent)
{
	if (nullptr == pComponentParent)
		return;
	TArray<USceneComponent*> arrayChildren;
	pComponentParent->GetChildrenComponents(true, arrayChildren);
	for (USceneComponent* pComponent : arrayChildren)
	{
		pComponent->DestroyComponent();
	}
}

FVector UMyActorCpt::GetActorLocation() const
{
	AActor* pActor = GetOwner();
	if (nullptr == pActor)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::GetActorLocation error, null == GetOwner(), name=%s", *GetName());
		return FVector::ZeroVector;
	}
	return pActor->GetActorLocation();
}

float UMyActorCpt::GetHorizontalDistanceTo(const FVector& locationTarget) const
{
	return (GetActorLocation() - locationTarget).Size2D();
}

FVector UMyActorCpt::GetHorizontalDirection(const FVector& locationTarget) const
{
	FVector v3Dir = locationTarget - GetActorLocation();
	v3Dir.Z = 0;
	v3Dir.Normalize();
	return v3Dir;
}

FRotator UMyActorCpt::GetHorizontalRotator(const FVector& locationTarget) const
{
	return GetHorizontalRotator(GetActorLocation(), locationTarget);
}

FRotator UMyActorCpt::GetHorizontalRotator(const FVector& locationStart, const FVector& locationTarget)
{
	FVector v3Dir = locationTarget - locationStart;
	v3Dir.Z = 0;
	v3Dir.Normalize();
	return v3Dir.Rotation();
}

FRotator UMyActorCpt::GetRotatorByLocates(const FVector& locationStart, const FVector& locationTarget)
{
	FVector v3Dir = locationTarget - locationStart;
	v3Dir.Normalize();
	return v3Dir.Rotation();
}

FVector2D UMyActorCpt::GetActorLocation2D() const
{
	AActor* pActor = GetOwner();
	if (nullptr == pActor)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::GetActorLocation error, null == GetOwner(), name=%s", *GetName());
		return FVector2D::ZeroVector;
	}
	FVector location = pActor->GetActorLocation();
	return FVector2D(location);
}

void UMyActorCpt::SetActorLocation(const FVector& location)
{
	AActor* pActor = GetOwner();
	if (nullptr == pActor)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::SetActorLocation error, null == GetOwner(), name=%s", *GetName());
		return;
	}
	pActor->SetActorLocation(location);
}
void UMyActorCpt::SetActorRotation(const FRotator& NewRotation)
{
	AActor* pActor = GetOwner();
	if (nullptr == pActor)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::SetActorRotation error, null == GetOwner(), name=%s", *GetName());
		return;
	}
	USceneComponent* pSceneComponent = pActor->GetRootComponent();
	if (nullptr == pSceneComponent)
		return;
	pSceneComponent->MoveComponent(FVector::ZeroVector, NewRotation, false);
}

FRotator UMyActorCpt::GetActorRotation() const
{
	AActor* pActor = GetOwner();
	if (nullptr == pActor)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::GetActorRotation error, null == GetOwner(), name=%s", *GetName());
		return FRotator::ZeroRotator;
	}
	return pActor->GetActorRotation();
}

void UMyActorCpt::InitializeComponent()
{
	Super::InitializeComponent();
	ActorComponentInitialize(this);
}

void UMyActorCpt::BeginPlay()
{
	Super::BeginPlay();
	ActorComponentBeginPlay(this, this);
}

void UMyActorCpt::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	ActorComponentEndPlay(this, this);
}

bool UMyActorCpt::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool bReplicate = NativeReplicateSubobjects(Channel, Bunch, RepFlags);
	return bReplicate;
}

bool UMyActorCpt::NativeReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	return false;
}

void UMyActorCpt::ActorComponentInitialize(UActorComponent* pActorComponent)
{
	UWorld* pWorld = pActorComponent->GetWorld();
	if (nullptr == pWorld)
		return;

	UAdminWorld* pAdminWorld = UAdminWorld::Get(pWorld);
	if (nullptr == pAdminWorld)
		return;

	pAdminWorld->BroadcastActorCptInitialize(pActorComponent);
}

void UMyActorCpt::ActorComponentBeginPlay(IComponentWrapper* pComponentWrapper, UActorComponent* pActorComponent)
{
	UWorld* pWorld = pActorComponent->GetWorld();
	if (nullptr == pWorld)
		return;
	UAdminWorld* pAdminWorld = UAdminWorld::Get(pWorld);
	if (nullptr == pAdminWorld)
		return;
	AActor* pActor = pActorComponent->GetOwner();
	if (nullptr == pActor)
		return;
	IEntityWrapper* pEntityWrapper = Cast<IEntityWrapper>(pActor);
	if (nullptr == pEntityWrapper)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::ActorComponentBeginPlay error, Owner is not IEntityWrapper, ActorComponentName=%s, OwnerName=%s", *pActorComponent->GetName(), *pActor->GetName());
		return;
	}

#if WITH_EDITOR
	const TSet<UActorComponent*>& setCpt = pActor->GetComponents();
	for (UActorComponent* pCpt : setCpt)
	{
		if (pCpt != pActorComponent && pCpt->GetClass()->GetName() == pActorComponent->GetClass()->GetName())
		{
			// MY_LOG(LogFrame, Fatal, "UMyActorCpt::ActorComponentBeginPlay error, %s repeat add in %s", *pActorComponent->GetName(), *pActor->GetName());
		}
	}
#endif

	pComponentWrapper->AssignComponent(pAdminWorld, pEntityWrapper->m_idEntity);
	pAdminWorld->BroadcastActorCptBeginPlay(pActorComponent);
}

void UMyActorCpt::ActorComponentEndPlay(IComponentWrapper* pComponentWrapper, UActorComponent* pActorComponent)
{
	UWorld* pWorld = pActorComponent->GetWorld();
	if (nullptr == pWorld/* || !pWorld->IsGameWorld()*/)
		return;
	AActor* pActor = pActorComponent->GetOwner();
	if (nullptr == pActor)
		return;
	UAdminWorld* pAdminWorld = UAdminWorld::Get(pWorld);
	if (nullptr == pAdminWorld)
		return;
	IEntityWrapper* pEntityWrapper = Cast<IEntityWrapper>(pActor);
	if (nullptr != pEntityWrapper)
	{
		if (pEntityWrapper->m_bCreate)
		{
			pComponentWrapper->RemoveComponent(pAdminWorld, pEntityWrapper->m_idEntity);
			pAdminWorld->BroadcastActorCptEndPlay(pActorComponent);
		}
	}
	else
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::EndPlay error, Owner is not IEntityWrapper, name=%s, OwnerName=%s", *pActorComponent->GetName(), *pActor->GetName());
	}
}

void UMyActorCpt::DestroyCptByName(AActor* pActor, FName name)
{
	if (nullptr == pActor)
	{
		// MY_LOG(LogFrame, Error, "UMyActorCpt::DestroyCptByName error, null == pOwner");
		return;
	}
	const TSet<UActorComponent*>& setComponent = pActor->GetComponents();
	for (UActorComponent* pComponent : setComponent)
	{
		if (name == pComponent->GetFName())
		{
			pComponent->DestroyComponent();
			return;
		}
	}
}