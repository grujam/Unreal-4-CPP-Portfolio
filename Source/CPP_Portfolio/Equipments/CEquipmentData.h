#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CEquipmentData.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCEquipmentData : public UObject
{
	GENERATED_BODY()

public:
	friend class UCEquipmentAsset;

private:
	UPROPERTY(VisibleAnywhere)
		class ACEquipment* Equipment;

	UPROPERTY(VisibleAnywhere)
		class UCEquip* Equip;

	UPROPERTY(VisibleAnywhere)
		class UCActions* Action;

public:
	FORCEINLINE ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE UCEquip* GetEquip() { return Equip; }
	FORCEINLINE UCActions* GetActions() { return Action; }
};
