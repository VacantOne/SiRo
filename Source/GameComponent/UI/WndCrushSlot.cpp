#include "WndCrushSlot.h"
#include "Components/Button.h"
//#include "UMG.h"
//#include "UMGStyle.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"

bool UWndCrushSlot::Initialize()
{
	return Super::Initialize();
}
TSharedRef<SWidget> UWndCrushSlot::RebuildWidget()
{
	return Super::RebuildWidget();
}

void UWndCrushSlot::NativeConstruct()
{
	Super::NativeConstruct();
	UButton* Btn = Cast<UButton>(GetWidgetFromName("Btn"));
	if (nullptr != Btn)
	{
		Btn->OnClicked.AddDynamic(this, &ThisClass::OnBtnClicked);
		auto a = GetRenderTransform().ToSlateRenderTransform();
	}
}

void UWndCrushSlot::OnBtnClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
	OnMouseButtonDouwn.ExecuteIfBound(index);
}