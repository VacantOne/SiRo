#pragma once
#include "MyCore/MySystem.h"
#include "CrushGameSystem.generated.h"

class UUserWidget;
class UGridPanel;
class UCanvasPanel;
class UWndCrushSlot;
class UImage;
class UButton;
class UTextBlock;

USTRUCT()
struct FCrushSlot
{
	GENERATED_BODY()
	int typeId;
	bool isCrushed;
	UWndCrushSlot* widget;
	int downUnit = 0;
};

UCLASS(BlueprintType, Blueprintable)
class UCrushGameSystem : public UMySystem
{
	GENERATED_BODY()
public:
	UCrushGameSystem();
	virtual void NativeInitSystem() override;
	void OnPlayerControllerCptBeginPlay(UActorComponent* pActorCpt);

	//void Init();
protected:
	virtual void NativeTick(float DeltaSeconds) override;
	//virtual void NativeTick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Crush Panel"))

	UUserWidget* CrushPanleWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Crush Slot"))

	TSubclassOf<UWndCrushSlot> CrushSlot;

	UCanvasPanel* m_pMyPanel;

	UImage* m_DymicSlot;

	UButton* m_CoverBtn;

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
	UFUNCTION()
	void OnSlotSelected(int index);
	UFUNCTION()
	void OnClickedCoverImg();

private:
	void CreatUnit(int index);
	FVector2D GetPosition(int index);
	FIntVector2 GetColumAndRow(int index);
	int GetRightSlotIndex(int index);
	int GetLeftSlotIndex(int index);
	int GetUpSlotIndex(int index);
	int GetDownSlotIndex(int index);

	TArray<FCrushSlot> m_ArrySlots;
	TArray<int> m_ArryCreateSlotIndex;

	int m_SelectedIndex = -1;
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

};
