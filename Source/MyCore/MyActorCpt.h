// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "ComponentWrapper.h"
#include "MyActorCpt.generated.h"

//地图Actor相关,上下线切换地图的时候自动删除
UCLASS(Blueprintable, Abstract)
class MYCORE_API UMyActorCpt : public UActorComponent, public IComponentWrapper
{
	GENERATED_BODY()

public:	
	UMyActorCpt();
	//一次遍历只能删一个
	void DestroyCptByName(const FName& name);
	static void DestroyChildren(USceneComponent* pComponentParent);

	FVector GetActorLocation() const;
	float GetHorizontalDistanceTo(const FVector& locationTarget) const;
	FVector GetHorizontalDirection(const FVector& locationTarget) const;
	//水平方向,忽略Z的方向
	FRotator GetHorizontalRotator(const FVector& locationTarget) const;
	static FRotator GetHorizontalRotator(const FVector& locationStart, const FVector& locationTarget);
	static FRotator GetRotatorByLocates(const FVector& locationStart, const FVector& locationTarget);
	FVector2D GetActorLocation2D() const;
	void SetActorLocation(const FVector& location);
	//由于Person把移动方向改为客户端输入,故此调用会无效,非Person的可调用,无网络同步
	void SetActorRotation(const FRotator& NewRotation);
	FRotator GetActorRotation() const;
	UFUNCTION(BlueprintCallable)
	static UActorComponent* CreateCpt(AActor* pActor, UClass* pClass = nullptr);


	template<class T>
	static T* CreateCpt(AActor* pActor, UClass* pClass = nullptr, FName name = NAME_None) //注意外面如果传name的时候必须保证唯一,否则会替换掉相同name的
	{
		if (nullptr == pActor)
		{
			//MY_LOG(LogFrame, Error, "UMyActorCpt::CreateCpt error, null == pOwner");
			return nullptr;
		}
		T* pT = nullptr;
		if (nullptr == pClass)
		{
			pT = NewObject<T>(pActor, name);
		}
		else
		{
			pT = NewObject<T>(pActor, pClass, name);
		}
		//支持动态创建的组件显示到Details面板上
		pActor->AddInstanceComponent(pT);
		pT->RegisterComponent();

		return pT;
	}

	static void DestroyCptByName(AActor* pActor, FName name);


	template<class T>
	static void DestroyCptIfExist(AActor* pActor)
	{
		if (nullptr == pActor)
		{
			//MY_LOG(LogFrame, Error, "UMyActorCpt::DestroyCpt error, null == pOwner");
			return;
		}
		TArray<T*> arrayCpt;
		pActor->GetComponents<T>(arrayCpt);
		if (0 == arrayCpt.Num())
		{
			return;
		}
		for (auto cptIter = arrayCpt.CreateConstIterator(); cptIter; ++cptIter)
		{
			(*cptIter)->DestroyComponent();
		}
		// 		for (auto pT : arrayCpt)
		// 		{
		// 			pT->DestroyComponent();
		// 		}
	}

	template<class T>
	FORCEINLINE_DEBUGGABLE static T* GetCpt(const UActorComponent* pActorComponent, bool bErrorNoFind = false)
	{
		AActor* pActor = pActorComponent->GetOwner();
		if (nullptr == pActor)
		{
			//MY_LOG(LogFrame, Fatal, "UMyActorCpt::GetCpt error, null == pActorComponent->GetOwner(), name=%s", *pActorComponent->GetName());
			return nullptr;
		}
#if WITH_EDITOR
		if (pActorComponent->GetClass() == T::StaticClass())
		{
			//MY_LOG(LogFrame, Warning, "UMyActorCpt::GetCpt 警告，不需要获取和自己相同类型的组件， 类名=%s", *pActorComponent->GetClass()->GetName());
		}
#endif
		return GetCpt<T>(pActor, bErrorNoFind);
	}

	//通过Actor的组件获取其他类型的组件
	//返回值：获取到的组件
	//pActorComponent:已知的组件
	UFUNCTION(BlueprintCallable, Category = "--MyActorCpt--")
	static UActorComponent* GetCpt(UActorComponent* pActorComponent, UClass* pClass);

	template<class T>
	static T* GetCpt(AActor* pActor, bool bErrorNoFind = false)
	{
		if (nullptr == pActor)
		{
			//MY_LOG(LogFrame, Fatal, "UMyActorCpt::GetCpt error, null == pActor");
			return nullptr;
		}
		T* pT = pActor->FindComponentByClass<T>();
		if (nullptr == pT && bErrorNoFind)
		{
			//MY_LOG(LogFrame, Error, "GetCpt 失败， Actor：%s找不到组件类：%s", *pActor->GetName(), *T::StaticClass()->GetName());
		}
		return pT;
	}

	template<class T>
	static T* GetCptByName(UActorComponent* pActorComponent, FName name, bool bIncludeFromChildActors = false)
	{
		AActor* pActor = pActorComponent->GetOwner();
		if (nullptr == pActor)
		{
			//MY_LOG(LogFrame, Fatal, "UMyActorCpt::GetCptByName error, null == pActorComponent->GetOwner(), Cpt name=%s, find name=%s", *pActorComponent->GetName(), *name.ToString());
			return nullptr;
		}

		TInlineComponentArray<T*> setComponent;
		pActor->GetComponents<T>(setComponent, bIncludeFromChildActors);

		for (UActorComponent* Component : setComponent)
		{
			if (Component->GetFName() == name)
			{
				if (T* pCpt = Cast<T>(Component))
					return pCpt;
			}
		}

		return nullptr;
	}

	template<class T>
	static T* GetCptByName(AActor* pActor, FName name, bool bIncludeFromChildActors = false)
	{
		TInlineComponentArray<T*> setComponent;
		pActor->GetComponents<T>(setComponent, bIncludeFromChildActors);
		for (UActorComponent* pComponent : setComponent)
		{
			if (pComponent->GetFName() == name)
			{
				if (T* pCpt = Cast<T>(pComponent))
					return pCpt;
			}
		}

		return nullptr;
	}



	template<class T>
	FORCEINLINE T* GetCpt(bool bErrorNoFind = false) const
	{
		return UMyActorCpt::GetCpt<T>(this, bErrorNoFind);
	}

	template<class T>
	T* GetCptByName(const FName& name) const
	{
		AActor* pActor = GetOwner();
		if (nullptr == pActor)
		{
			//MY_LOG(LogFrame, Fatal, "UMyActorCpt::GetCptByClassByName error, null == GetOwner(), name=%s", *GetName());
			return nullptr;
		}
		UClass* pClass = T::StaticClass();
		const TSet<UActorComponent*>& setComponent = pActor->GetComponents();
		for (UActorComponent* pComponent : setComponent)
		{
			if (pComponent->GetFName() == name
				&& pComponent->IsA(pClass))
			{
				return (T*)(pComponent);
			}
		}
		return nullptr;
	}

	template<class T>
	FORCEINLINE T* FindOrAddCpt(UClass* pClass = nullptr, FName name = NAME_None)
	{
		return FindOrAddCpt<T>(this, pClass, name);
	}

	template<class T>
	static T* FindOrAddCpt(UActorComponent* pActorComponent, UClass* pClass = nullptr, FName name = NAME_None)
	{
		T* pT = nullptr;
		if (name.IsNone())
		{
			pT = GetCpt<T>(pActorComponent);
		}
		else
		{
			pT = GetCptByName<T>(pActorComponent, name);
		}
		if (nullptr != pT)
			return pT;
		AActor* pActor = pActorComponent->GetOwner();
		if (nullptr == pActor)
		{
			//MY_LOG(LogFrame, Fatal, "UMyActorCpt::FindOrAddCpt error, null == pActorComponent->GetOwner(), name=%s", *pActorComponent->GetName());
			return nullptr;
		}
		return CreateCpt<T>(pActor, pClass, name);
	}

	template<class T>
	T* GetCptByTag(const FName& tag) const
	{
		AActor* pActor = GetOwner();
		if (nullptr == pActor)
		{
			//MY_LOG(LogFrame, Fatal, "UMyActorCpt::GetCptByClassByName error, null == GetOwner(), name=%s", *GetName());
			return nullptr;
		}
		UClass* pClass = T::StaticClass();
		const TSet<UActorComponent*>& setComponent = pActor->GetComponents();
		for (UActorComponent* pComponent : setComponent)
		{
			if (pComponent->ComponentHasTag(tag)
				&& pComponent->IsA(pClass))
			{
				return (T*)(pComponent);
			}
		}
		return nullptr;
	}

protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual bool NativeReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags  *RepFlags);
public:
	static void ActorComponentInitialize(UActorComponent* pActorComponent);
 	static void ActorComponentBeginPlay(IComponentWrapper* pComponentWrapper, UActorComponent* pActorComponent);
	static void ActorComponentEndPlay(IComponentWrapper* pComponentWrapper, UActorComponent* pActorComponent);
private:
	//不允许子类重写，有需要请使用NativeReplicateSubobjects
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags  *RepFlags) override final;
};
