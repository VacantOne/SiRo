#include "WndCrushSlot.h"
#include "Components/Button.h"
//#include "UMG.h"
//#include "UMGStyle.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"

bool UWndCrushSlot::Initialize()
{
	UButton* Btn = Cast<UButton>(GetWidgetFromName("Btn"));
	if (nullptr != Btn)
	{
		//UE_LOG(LogTemp, Warning, TEXT("************Initialize Widget"));
			//Btn->OnClicked.AddDynamic(this, &ThisClass::OnBtnClicked);
	}
	return Super::Initialize();
}
TSharedRef<SWidget> UWndCrushSlot::RebuildWidget()
{
	UButton* Btn = Cast<UButton>(GetWidgetFromName("Btn"));
	if (nullptr != Btn)
	{
		//Btn->OnClicked.AddDynamic(this, &ThisClass::OnBtnClicked);
		//UE_LOG(LogTemp, Warning, TEXT("*********Rebuild Widget"));
	}
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