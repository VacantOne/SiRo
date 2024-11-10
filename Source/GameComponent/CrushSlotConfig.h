#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "CrushSlotConfig.generated.h"

USTRUCT(BlueprintType)
struct FCrushSlotConfig : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	// 类型索引
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TypeId;

	// 类型名称
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FColor Color;
};
