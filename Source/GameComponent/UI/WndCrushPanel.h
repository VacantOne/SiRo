#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WndCrushPanel.generated.h"

class UWndCrushSlot;
class UCanvasPanel;
class UImage;
class UButton;

USTRUCT()
struct FCrushSlot
{
	GENERATED_BODY()
	int typeId;
	bool isCrushed;
	UWndCrushSlot* widget;
	int downUnit = 0;
};


UCLASS(BlueprintType)
class GAMECOMPONENT_API UWndCrushPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Crush Slot"))
	TSubclassOf<UWndCrushSlot> CrushSlotClass;

	UCanvasPanel* m_pMyOperatePanel;

	UImage* m_DymicSlot;
	UButton* m_CoverBtn;
private:
	UFUNCTION()
	void OnSlotSelected(int index);
	UFUNCTION()
	void OnClickedCoverImg();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Panel Colums"))
	int m_Colums = 7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Panel Rows"))
	int m_Rows = 7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Slot Width"))
	float m_SlotWidth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Slot Height"))
	float m_SlotHeight = 100;
private:
	TArray<FCrushSlot> m_ArrySlots;
	TArray<int> m_ArryCreateSlotIndex;

	int m_SelectedIndex = -1;
private:
	void CreateUnit(int index);

	FVector2D GetPosition(int index);
	FIntVector2 GetColumAndRow(int index);
	int GetRightSlotIndex(int index);
	int GetLeftSlotIndex(int index);
	int GetUpSlotIndex(int index);
	int GetDownSlotIndex(int index);

private:
	void OperateCrush();
	void FullPanel();
private:
	FTimerHandle MyTimerHandle;
	int m_TimerCount;
	float m_Duration = 0.5;

	void SlotInsertAnimHandle(TArray<int> indexArray, float duration);
	void SlotCrushAnimHandle(float duration);
	void SlotFullAnimHandle(float duration);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

};

