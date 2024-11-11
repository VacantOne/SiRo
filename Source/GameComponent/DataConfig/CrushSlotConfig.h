#include "CoreMinimal.h"
//#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "CrushSlotConfig.generated.h"

USTRUCT(BlueprintType)
struct FCrushSlotConfig : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TypeId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FColor Color;
};
