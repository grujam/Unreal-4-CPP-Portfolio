#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipments/CEquipmentStructures.h"
#include "CEquipmentComponent.generated.h"

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	LongSword, DualBlade, Hammer, Spear, OHSword, Bow, Unarmed
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEquipmentTypeChanged, EEquipmentType, InPrevType, EEquipmentType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCEquipmentComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, Category = "EquipmentAsset")
		class UCEquipmentAsset* EquipmentAsset[(int32)EEquipmentType::Unarmed];

private:
	UPROPERTY()
		class UCEquipmentData* EquipmentData[(int32)EEquipmentType::Unarmed];

public:
	FORCEINLINE EEquipmentType GetType() { return Type; }

	FORCEINLINE bool IsUnarmedMode() { return Type == EEquipmentType::Unarmed; }
	FORCEINLINE bool IsLongSwordMode() { return Type == EEquipmentType::LongSword; }
	FORCEINLINE bool IsDualBladeMode() { return Type == EEquipmentType::DualBlade; }
	FORCEINLINE bool IsHammerMode() { return Type == EEquipmentType::Hammer; }
	FORCEINLINE bool IsSpearMode() { return Type == EEquipmentType::Spear; }
	FORCEINLINE bool IsOHSwordMode() { return Type == EEquipmentType::OHSword; }
	FORCEINLINE bool IsBowMode() { return Type == EEquipmentType::Bow; }

	FORCEINLINE void LeftPressed() { bKeyLeft = true; }
	FORCEINLINE void RightPressed() { bKeyRight = true; }
	FORCEINLINE void ExtraPressed() { bKeyExtra = true; }
	FORCEINLINE void ResetKeys() { bKeyLeft = false; bKeyRight = false; bKeyExtra = false; }

public:
	class ACEquipment* GetEquipment();
	class UCEquip* GetEquip();
	class UCActions* GetActions();

public:
	void SetUnarmedMode();
	void SetLongSwordMode();
	void SetDualBladeMode();
	void SetHammerMode();
	void SetSpearMode();
	void SetOHSwordMode();
	void SetBowMode();

public:
	void WaitAction();
	void DoAction();
	void DoActionLeft();
	void DoActionRight();
	void DoActionDouble();
	void DoActionExtra();
	void DoActionExtraLeft();
	void DoActionExtraRight();

public:
	bool IsIdleState();
	void ChangeType(EEquipmentType InType);

private:
	void SetMode(EEquipmentType InType);

public:
	FEquipmentTypeChanged OnEquipmentTypeChanged;

private:
	class ACharacter* OwnerCharacter;

	EEquipmentType Type = EEquipmentType::Unarmed;
	EEquipmentType PrevType = EEquipmentType::Unarmed;

	FTimerHandle TimerHandle;

	bool bKeyLeft;
	bool bKeyRight;
	bool bKeyExtra;
};
