#include "CrushGameSystem.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/CanvasPanel.h"
#include "Components/GridSlot.h"
#include "Components/SizeBox.h"
#include "Components//CanvasPanelSlot.h"
#include "Components/Image.h"
#include <Components/Button.h>
#include "GameComponent/DataConfig/CrushSlotConfig.h"
#include "GameComponent/UI/WndCrushSlot.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Engine/DataTable.h> 
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "GameBase/MyPlayerControllerCpt.h"

const int s_NeedFlushCount = 50;

UCrushGameSystem::UCrushGameSystem()
{
}

void UCrushGameSystem::OnClickedCoverImg()
{
    UE_LOG(LogTemp, Warning, TEXT("========= clicked cover img"));
    if (m_SelectedIndex != -1)
    {
        SlotInsertAnimHandle(TArray<int>{m_SelectedIndex}, m_Duration);
        m_SelectedIndex = -1;
        m_DymicSlot->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UCrushGameSystem::OnPlayerControllerCptBeginPlay(UActorComponent* pActorCpt)
{
    UE_LOG(LogTemp, Warning, TEXT("=============== playerCpt!!!!!!!!!!!"));
    UDataTable* dataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/cfg_CrushSlot.cfg_CrushSlot")));
    /// Script / UMGEditor.WidgetBlueprint'/Game/ArtRes/UI/MyCrushSlot.MyCrushSlot'
    // 初始化UI
    CrushSlot = StaticLoadClass(UWndCrushSlot::StaticClass(), nullptr, TEXT("/Game/ArtRes/UI/MyCrushSlot.MyCrushSlot_C"));

    UClass* WidgetClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("/Game/ArtRes/UI/CrashPanel.CrashPanel_C"));
    CrushPanleWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
    if (nullptr != CrushPanleWidget)
    {
        CrushPanleWidget->AddToViewport(0);
    }

    m_pMyPanel = Cast<UCanvasPanel>(CrushPanleWidget->GetWidgetFromName(TEXT("MyPanel")));
    //m_pMyPanel->OnMouseButtonDouwn.BindUFunction(this, FName("OnSlotSelected"));

    m_DymicSlot = Cast<UImage>(CrushPanleWidget->GetWidgetFromName(TEXT("MyDymicSlot")));
    m_CoverBtn = Cast<UButton>(CrushPanleWidget->GetWidgetFromName(TEXT("CoverImg")));
    m_CoverBtn->OnClicked.AddDynamic(this, &UCrushGameSystem::OnClickedCoverImg);
    //m_CoverImg->OnMouseButtonDownEvent.BindUFunction(this, FName("OnClickedCoverImg"));

    for (int row = 0; row < m_Rows; row++)
    {
        for (int colum = 0; colum < m_Colums; colum++)
        {
            CreatUnit(m_ArrySlots.Num());
        }
    }

    OperateCrush();
}

void UCrushGameSystem::NativeInitSystem()
{
    QueryCptBeginPlay<UMyPlayerControllerCpt>().AddUObject(this, &ThisClass::OnPlayerControllerCptBeginPlay);
}

void UCrushGameSystem::NativeTick(float DeltaSeconds)
{
    Super::NativeTick(DeltaSeconds);
    
    if (m_SelectedIndex != -1)
    {
        FVector2D pos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(m_DymicSlot->Slot);
        CanvasSlot->SetPosition(pos);
    }

}

void UCrushGameSystem::CreatUnit(int index)
{
    UDataTable* dataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/cfg_CrushSlot.cfg_CrushSlot")));
    int typeId = FMath::RandRange(0, 4); // 4
    FCrushSlotConfig* slotCongif = dataTable->FindRow<FCrushSlotConfig>(*FString::FromInt(typeId), TEXT("CrushSlot"));

    UWndCrushSlot* SlotWidget = Cast<UWndCrushSlot>(CreateWidget<UUserWidget>(GetWorld(), CrushSlot));
    m_pMyPanel->AddChildToCanvas(SlotWidget);

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


FVector2D UCrushGameSystem::GetPosition(int index)
{
    FIntVector2 indexPostion = GetColumAndRow(index);
    return  FVector2D(indexPostion.X * m_SlotWidth, indexPostion.Y * m_SlotHeight);
}

FIntVector2 UCrushGameSystem::GetColumAndRow(int index)
{
    int X = index % m_Colums;
    int Y = index / m_Colums;
    return FIntVector2(X, Y);
}

int UCrushGameSystem::GetRightSlotIndex(int index)
{
    FIntVector2 pos = GetColumAndRow(index);
    return (pos.X < m_Colums - 1) ? pos.Y * m_Colums + pos.X + 1 : -1;
}
int UCrushGameSystem::GetDownSlotIndex(int index)
{
    FIntVector2 pos = GetColumAndRow(index);
    return (pos.Y < m_Rows - 1) ? pos.Y * m_Colums + pos.X + m_Colums : -1;
}
int UCrushGameSystem::GetLeftSlotIndex(int index)
{
    FIntVector2 pos = GetColumAndRow(index);
    return (pos.X > 0) ? pos.Y * m_Colums + pos.X - 1 : -1;
}
int UCrushGameSystem::GetUpSlotIndex(int index)
{
    FIntVector2 pos = GetColumAndRow(index);
    return  (pos.Y > 0) ? pos.Y * m_Colums + pos.X - m_Colums : -1;
}

void UCrushGameSystem::OperateCrush()
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

    // 记录下降
    //for (int index = 0; index < m_ArrySlots.Num(); index++)
    //{
    //    int downUnit = 0;
    //    int downPoint = GetDownSlotIndex(index);
    //    while (downPoint != -1)
    //    {
    //        if(m_ArrySlots[downPoint].isCrushed)
    //            downUnit++;
    //        
    //        downPoint = GetDownSlotIndex(downPoint);
    //    }
    //    m_ArrySlots[index].downUnit = downUnit;
    //    //UE_LOG(LogTemp, Warning, TEXT("**************======== [%d]"), m_ArrySlots[index].downUnit);
    //}
    //
    if (bNeedCrush)
    {
        //UE_LOG(LogTemp, Warning, TEXT("EndWithTrue ============== FullPanel "));
        SlotCrushAnimHandle(m_Duration);
        m_pMyPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
    }
    else
    {
        m_pMyPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    }
}

void UCrushGameSystem::FullPanel()
{
    UE_LOG(LogTemp, Warning, TEXT("Start ============== FullPanel "));

    //int index1 = 0;
    //for (int row = 0; row < m_Rows; row++)
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("Row : %d =================================="), row);

    //    for (int colum = 0; colum < m_Colums; colum++)
    //    {
    //        UE_LOG(LogTemp, Warning, TEXT("[%d] index: [%d] : %d"), colum, index1, m_ArrySlots[index1].downUnit);
    //        index1++;
    //    }
    //}

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

    /*   index1 = 0;
       for (int row = 0; row < m_Rows; row++)
       {
           UE_LOG(LogTemp, Warning, TEXT("Row : %d =================================="), row);

           for (int colum = 0; colum < m_Colums; colum++)
           {
               if (m_ArrySlots[index1].isCrushed)
               {
                   UE_LOG(LogTemp, Warning, TEXT("[%d] index: [%d] : %d"), colum, index1, m_ArrySlots[index1].downUnit);
               }

               index1++;
           }
       }*/


       //m_ArryCreateSlotIndex.Empty();
    for (int colums = 0; colums < m_Colums; colums++)
    {
        TArray<int> arrySlot;
        if (m_ArrySlots[colums].isCrushed)
        {
            arrySlot.Add(colums);
            CreatUnit(colums);
            //m_ArrySlots[colums].downUnit++;
            //m_ArryCreateSlotIndex.Add(colums);
            int downPoint = GetDownSlotIndex(colums);
            while (downPoint != -1 && m_ArrySlots[downPoint].isCrushed)
            {
                arrySlot.Add(downPoint);
                //m_ArryCreateSlotIndex.Add(downPoint);
                CreatUnit(downPoint);
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


void UCrushGameSystem::OnSlotSelected(int index)
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

void UCrushGameSystem::SlotInsertAnimHandle(TArray<int> indexArray, float duration)
{
    UE_LOG(LogTemp, Warning, TEXT("Start ============== SlotChangeAnimHandle "));
    if (indexArray.Num() < 1)
        return;

    m_pMyPanel->SetVisibility(ESlateVisibility::HitTestInvisible);

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

            m_pMyPanel->SetVisibility(ESlateVisibility::Visible);

            OperateCrush();
        }
        }, duration / s_NeedFlushCount, true);
}

void UCrushGameSystem::SlotCrushAnimHandle(float duration)
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

void UCrushGameSystem::SlotFullAnimHandle(float duration)
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

//void UCrushGameSystem::Tick(float DeltaSeconds)
//{
//    Super::Tick(DeltaSeconds);
//    FVector2D pos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
//
//    UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(m_DymicSlot->Slot);
//    CanvasSlot->SetPosition(pos);
//}