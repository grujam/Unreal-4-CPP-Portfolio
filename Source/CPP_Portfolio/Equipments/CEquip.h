#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CEquipmentStructures.h"
#include "CEquip.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipBeginEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipBeginUnequip);

UCLASS()
class CPP_PORTFOLIO_API UCEquip : public UObject
{
	GENERATED_BODY()

public:
	void BeginPlay(class ACharacter* InOwner, const FEquipData& InEquipData, const FEquipData& InUnequipData);

public:
	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void UnEquip();
	void UnEquip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Unequip();
	void Begin_Unequip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void End_Unequip();
	void End_Unequip_Implementation();

public:
	FEquipBeginEquip OnEquipmentBeginEquip;
	FEquipBeginUnequip OnEquipmentUnequip;

private:
	class ACharacter* OwnerCharacter;
	FEquipData EquipData;
	FEquipData UnequipData;

private:
	class UCMovementComponent* MovementComponent;
	class UCStateComponent* StateComponent;

private:
	bool bBeginEquip;
	bool bBeginUnequip;
	bool bEquipped;
};