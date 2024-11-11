#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WndCrushSlot.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMouseButtonDouwn, int, index);


UCLASS(BlueprintType)
class GAMECOMPONENT_API UWndCrushSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int index;
	UPROPERTY()
	FOnMouseButtonDouwn OnMouseButtonDouwn;

	virtual bool Initialize() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeConstruct();

private:
	UFUNCTION()
	void OnBtnClicked();
};

