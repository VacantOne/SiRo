#include "WndCrushPanel.h"
#include <Engine/DataTable.h>
#include <Components/CanvasPanel.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/Image.h>
#include <Components/Button.h>
#include <TimerManager.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include "WndCrushSlot.h"
#include "DataConfig/CrushSlotConfig.h"

const int s_NeedFlushCount = 50;

void UWndCrushPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    if (m_SelectedIndex != -1)
    {
        FVector2D pos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(m_DymicSlot->Slot);
        CanvasSlot->SetPosition(pos);
    }
}

void UWndCrushPanel::NativeConstruct()
{
	Super::NativeConstruct();

	UDataTable* dataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/cfg_CrushSlot.cfg_CrushSlot")));

	CrushSlotClass = StaticLoadClass(UWndCrushSlot::StaticClass(), nullptr, TEXT("/Game/ArtRes/UI/MyCrushSlot.MyCrushSlot_C"));
	m_pMyOperatePanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("MyPanel")));
	m_DymicSlot = Cast<UImage>(GetWidgetFromName(TEXT("MyDymicSlot")));
	m_CoverBtn = Cast<UButton>(GetWidgetFromName(TEXT("CoverImg")));
	m_CoverBtn->OnClicked.AddDynamic(this, &UWndCrushPanel::OnClickedCoverImg);

	for (int row = 0; row < m_Rows; row++)
	{
		for (int colum = 0; colum < m_Colums; colum++)
		{
			CreateUnit(m_ArrySlots.Num());
		}
	}

	OperateCrush();
}

void UWndCrushPanel::CreateUnit(int index)
{
    UDataTable* dataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/cfg_CrushSlot.cfg_CrushSlot")));
    int typeId = FMath::RandRange(0, 4); // 4
    FCrushSlotConfig* slotCongif = dataTable->FindRow<FCrushSlotConfig>(*FString::FromInt(typeId), TEXT("CrushSlot"));

    UWndCrushSlot* SlotWidget = Cast<UWndCrushSlot>(CreateWidget<UUserWidget>(GetWorld(), CrushSlotClass));
    m_pMyOperatePanel->AddChildToCanvas(SlotWidget);

    SlotWidget->SetColorAndOpacity(slotCongif->Color);
    SlotWidget->index = index;
    SlotWidget->OnMouseButtonDouwn.BindUFunction(this, FName("OnSlotSelected"));

    SlotWidget->SetPositionInViewport(GetPosition(index));
    UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SlotWidget->Slot);
    if (nullptr != CanvasSlot)
    {
        CanvasSlot->SetPosition(GetPosition(index));
        CanvasSlot->SetSize(FVector2D(m_SlotWidth, m_SlotHeight));
    }

    UE_LOG(LogTemp, Warning, TEXT("***** pos : %f , %f"), GetPosition(m_ArrySlots.Num()).X, GetPosition(m_ArrySlots.Num()).Y);
    UWidget* tag = SlotWidget->GetWidgetFromName(TEXT("Tag"));
    if (nullptr != tag)
        tag->SetVisibility(ESlateVisibility::Hidden);
    FCrushSlot slot;
    slot.typeId = typeId;
    slot.isCrushed = false;
    slot.widget = SlotWidget;
    slot.downUnit = 0;

    if (m_ArrySlots.Num() <= index)
        m_ArrySlots.Add(slot);
    else
        m_ArrySlots[index] = slot;
}

FVector2D UWndCrushPanel::GetPosition(int index)
{
    FIntVector2 indexPostion = GetColumAndRow(index);
    return  FVector2D(indexPostion.X * m_SlotWidth, indexPostion.Y * m_SlotHeight);
}

FIntVector2 UWndCrushPanel::GetColumAndRow(int index)
{
    int X = index % m_Colums;
    int Y = index / m_Colums;
    return FIntVector2(X, Y);
}

int UWndCrushPanel::GetRightSlotIndex(int index)
{
    FIntVector2 pos = GetColumAndRow(index);
    return (pos.X < m_Colums - 1) ? pos.Y * m_Colums + pos.X + 1 : -1;
}
int UWndCrushPanel::GetDownSlotIndex(int index)
{
    FIntVector2 pos = GetColumAndRow(index);
    return (pos.Y < m_Rows - 1) ? pos.Y * m_Colums + pos.X + m_Colums : -1;
}
int UWndCrushPanel::GetLeftSlotIndex(int index)
{
    FIntVector2 pos = GetColumAndRow(index);
    return (pos.X > 0) ? pos.Y * m_Colums + pos.X - 1 : -1;
}
int UWndCrushPanel::GetUpSlotIndex(int index)
{
    FIntVector2 pos = GetColumAndRow(index);
    return  (pos.Y > 0) ? pos.Y * m_Colums + pos.X - m_Colums : -1;
}

void UWndCrushPanel::OperateCrush()
{
    UE_LOG(LogTemp, Warning, TEXT("Start ============== OperateCrush "));
    bool bNeedCrush = false;
    // 标记横排消除
    for (int index = 0; index < m_ArrySlots.Num(); index++)
    {
        TArray<int> CrushList;
        CrushList.Add(index);
        int point = GetRightSlotIndex(index);
        while (point != -1 && m_ArrySlots[index].typeId == m_ArrySlots[point].typeId)
        {
            CrushList.Add(point);
            point = GetRightSlotIndex(point);
        }

        if (CrushList.Num() >= 3)
        {
            for (int CrushId : CrushList)
            {
                m_ArrySlots[CrushId].isCrushed = true;
                //UUserWidget* widget = Cast<UUserWidget>(m_pGridPanel->GetChildAt(CrushId));
                UUserWidget* widget = Cast<UUserWidget>(m_ArrySlots[CrushId].widget);
                UWidget* tag = widget->GetWidgetFromName(TEXT("Tag"));
                if (nullptr != tag)
                    tag->SetVisibility(ESlateVisibility::Visible);
                bNeedCrush = true;
            }
            index = CrushList.Last();
        }
    }

    // 标记竖排消除
    for (int index = 0; index < m_ArrySlots.Num(); index++)
    {
        TArray<int> CrushList;
        CrushList.Add(index);
        int point = GetDownSlotIndex(index);
        while (point != -1 && m_ArrySlots[index].typeId == m_ArrySlots[point].typeId)
        {
            CrushList.Add(point);
            point = GetDownSlotIndex(point);
        }

        if (CrushList.Num() >= 3)
        {
            for (int CrushId : CrushList)
            {
                m_ArrySlots[CrushId].isCrushed = true;
                //UUserWidget* widget = Cast<UUserWidget>(m_pGridPanel->GetChildAt(CrushId));
                UUserWidget* widget = Cast<UUserWidget>(m_ArrySlots[CrushId].widget);
                UWidget* tag = widget->GetWidgetFromName(TEXT("Tag"));
                if (nullptr != tag)
                    tag->SetVisibility(ESlateVisibility::Visible);
                bNeedCrush = true;
            }
        }
    }

    if (bNeedCrush)
    {
        //UE_LOG(LogTemp, Warning, TEXT("EndWithTrue ============== FullPanel "));
        SlotCrushAnimHandle(m_Duration);
        m_pMyOperatePanel->SetVisibility(ESlateVisibility::HitTestInvisible);
    }
    else
    {
        m_pMyOperatePanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    }
}

void UWndCrushPanel::FullPanel()
{
    UE_LOG(LogTemp, Warning, TEXT("Start ============== FullPanel "));

    bool bIsChanged = true;
    while (bIsChanged)
    {
        bIsChanged = false;
        for (int index = 0; index < m_ArrySlots.Num(); index++)
        {
            if (m_ArrySlots[index].isCrushed)
                continue;

            int downPoint = GetDownSlotIndex(index);
            if (downPoint != -1 && m_ArrySlots[downPoint].isCrushed)
            {
                m_ArrySlots[downPoint] = m_ArrySlots[index];
                m_ArrySlots[index].isCrushed = true;
                m_ArrySlots[downPoint].downUnit++;
                m_ArrySlots[downPoint].widget->index = downPoint;
                FVector2D pos = GetPosition(downPoint);
                UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(m_ArrySlots[downPoint].widget->Slot);
                CanvasSlot->SetPosition(FVector2D(pos.X, pos.Y));
                bIsChanged = true;
            }
        }
    }

    for (int colums = 0; colums < m_Colums; colums++)
    {
        TArray<int> arrySlot;
        if (m_ArrySlots[colums].isCrushed)
        {
            arrySlot.Add(colums);
            CreateUnit(colums);
            //m_ArrySlots[colums].downUnit++;
            //m_ArryCreateSlotIndex.Add(colums);
            int downPoint = GetDownSlotIndex(colums);
            while (downPoint != -1 && m_ArrySlots[downPoint].isCrushed)
            {
                arrySlot.Add(downPoint);
                //m_ArryCreateSlotIndex.Add(downPoint);
                CreateUnit(downPoint);
                //for (int index = 0; index < arrySlot.Num(); index++)
                //{
                //    m_ArrySlots[arrySlot[index]].downUnit++;
                //}
                downPoint = GetDownSlotIndex(downPoint);
            }
        }

        for (int i = 0; i < arrySlot.Num(); i++)
        {
            int index = arrySlot[i];
            m_ArrySlots[index].downUnit = arrySlot.Num();
        }
    }

    SlotFullAnimHandle(m_Duration);
}


void UWndCrushPanel::OnSlotSelected(int index)
{
    UE_LOG(LogTemp, Warning, TEXT(" ************** selected index : %d"), index);
    if (m_SelectedIndex == -1)
    {
        m_SelectedIndex = index;
        m_DymicSlot->SetVisibility(ESlateVisibility::HitTestInvisible);

        // 复制属性
        UWndCrushSlot* selectedSlot = m_ArrySlots[index].widget;
        m_DymicSlot->SetColorAndOpacity(selectedSlot->GetColorAndOpacity());

        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(m_DymicSlot->Slot);
        CanvasSlot->SetSize(FVector2D(m_SlotWidth, m_SlotHeight));

        //SetActorTickEnabled(true);
    }
    else if (m_SelectedIndex != index)
    {
        m_DymicSlot->SetVisibility(ESlateVisibility::Hidden);

        // 数据交换逻辑
        FCrushSlot tempSlot = m_ArrySlots[index];
        m_ArrySlots[index] = m_ArrySlots[m_SelectedIndex];
        m_ArrySlots[m_SelectedIndex] = tempSlot;
        m_ArrySlots[index].widget->index = index;
        m_ArrySlots[m_SelectedIndex].widget->index = m_SelectedIndex;

        // 交换动画
        SlotInsertAnimHandle(TArray<int>{index, m_SelectedIndex}, m_Duration);

        m_SelectedIndex = -1;
        //SetActorTickEnabled(false);
    }
}

void UWndCrushPanel::OnClickedCoverImg()
{
    UE_LOG(LogTemp, Warning, TEXT("========= clicked cover img"));
    if (m_SelectedIndex != -1)
    {
        SlotInsertAnimHandle(TArray<int>{m_SelectedIndex}, m_Duration);
        m_SelectedIndex = -1;
        m_DymicSlot->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UWndCrushPanel::SlotInsertAnimHandle(TArray<int> indexArray, float duration)
{
    UE_LOG(LogTemp, Warning, TEXT("Start ============== SlotChangeAnimHandle "));
    if (indexArray.Num() < 1)
        return;

    m_pMyOperatePanel->SetVisibility(ESlateVisibility::HitTestInvisible);

    for (int i = 0; i < indexArray.Num(); i++)
    {
        int index = indexArray[i];
        //UE_LOG(LogTemp, Warning, TEXT("============== insert index %d"), index);

        UWndCrushSlot* widget = m_ArrySlots[index].widget;
        widget->SetRenderScale(FVector2D(2));
        widget->SetVisibility(ESlateVisibility::Visible);
        //widget->SetZ
        FVector2D pos = GetPosition(index);
        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(widget->Slot);
        CanvasSlot->SetPosition(pos);
        CanvasSlot->SetZOrder(1);
    }
    m_TimerCount = 0;
    GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, [this, indexArray, duration]() {
        for (int i = 0; i < indexArray.Num(); i++)
        {
            int index = indexArray[i];
            UWndCrushSlot* widget = m_ArrySlots[index].widget;
            widget->SetRenderScale(FVector2D(2 - m_TimerCount / static_cast<float>(s_NeedFlushCount)));
        }
        m_TimerCount++;
        if (m_TimerCount > s_NeedFlushCount)
        {
            for (int i = 0; i < indexArray.Num(); i++)
            {
                int index = indexArray[i];
                UWndCrushSlot* widget = m_ArrySlots[index].widget;
                widget->SetRenderScale(FVector2D(1));
                UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(widget->Slot);
                CanvasSlot->SetZOrder(0);
            }
            GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);

            m_pMyOperatePanel->SetVisibility(ESlateVisibility::Visible);

            OperateCrush();
        }
        }, duration / s_NeedFlushCount, true);
}

void UWndCrushPanel::SlotCrushAnimHandle(float duration)
{
    UE_LOG(LogTemp, Warning, TEXT("Start ============== SlotCrushAnimHandle "));

    m_TimerCount = 0;
    GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, [this, duration]() {
        for (int index = 0; index < m_ArrySlots.Num(); index++)
        {
            if (m_ArrySlots[index].isCrushed)
            {
                m_ArrySlots[index].widget->SetRenderScale(FVector2D(1 - m_TimerCount * 0.02, 1 - m_TimerCount * 0.02));
            }
        }
        m_TimerCount++;
        if (m_TimerCount > s_NeedFlushCount)
        {
            GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
            //SlotMoveAnimHandle();
            FullPanel();
        }
        }, duration / s_NeedFlushCount, true);
}

void UWndCrushPanel::SlotFullAnimHandle(float duration)
{
    UE_LOG(LogTemp, Warning, TEXT("Start ============== SlotFullAnimHandle "));

    for (int index = 0; index < m_ArrySlots.Num(); index++)
    {
        m_ArrySlots[index].widget->SetRenderTranslation(FVector2D(0, -m_SlotHeight * m_ArrySlots[index].downUnit));
    }

    m_TimerCount = 0;
    GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, [this /*duration*/]() {
        //for (int j = 0; j < m_ArryCreateSlotIndex.Num(); j++)
        for (int index = 0; index < m_ArrySlots.Num(); index++)
        {
            if (m_ArrySlots[index].downUnit > 0)
            {
                float s = (m_TimerCount / static_cast<float>(s_NeedFlushCount) - 1) * m_SlotHeight * (m_ArrySlots[index].downUnit);
                int downUnit = m_ArrySlots[index].downUnit;
                //UE_LOG(LogTemp, Warning, TEXT(" s =========== %f  ==== %d ===== %d"), s, m_TimerCount, downUnit);
                m_ArrySlots[index].widget->SetRenderTranslation(FVector2D(0, s));
            }
        }

        m_TimerCount++;
        if (m_TimerCount > s_NeedFlushCount)
        {
            GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
            for (int index = 0; index < m_ArrySlots.Num(); index++)
            {
                //int index = m_ArryCreateSlotIndex[k];
                if (m_ArrySlots[index].downUnit > 0)
                {
                    m_ArrySlots[index].widget->SetRenderTranslation(FVector2D(0, 0));
                    m_ArrySlots[index].downUnit = 0;
                }
            }
            OperateCrush();
        }
        }, duration / s_NeedFlushCount, true);
}