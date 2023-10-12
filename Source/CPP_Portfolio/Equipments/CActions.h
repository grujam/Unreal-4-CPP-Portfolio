#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Equipments/CEquipmentStructures.h"
#include "CActions.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCActions : public UObject
{
	GENERATED_BODY()

public:
	UCActions();

	virtual void BeginPlay
	(
		class ACEquipment* InEquipment,
		class UCEquip* InEquip,
		class ACharacter* InOwner,
		class TArray<FActionDataArray>& InActionDataArray
	);

public:
	virtual void Action(EActionType InType);
	virtual void Begin_Action();
	virtual void End_Action();

public:
	FORCEINLINE void EnableNextAction() { bEnableNext = true; }
	FORCEINLINE void DisableNextAction() { bEnableNext = false; }

public:
	UFUNCTION()
		virtual void OnEquipmentOnCollision() {}

	UFUNCTION()
		virtual void OnEquipmentEndCollision();

	UFUNCTION()
		virtual void OnEquipmentBeginOverlap(class UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex, class ACharacter* InAttacker, class AActor* InAttackActor, class AActor* InOther, FHitResult SweepResult);

	UFUNCTION()
		virtual void OnEquipmentEndOverlap(class ACharacter* InAttacker, class AActor* InOther);

protected:
	bool bBeginAction;

	class ACharacter* OwnerCharacter;
	class UWorld* World;

	class UCMovementComponent* MovementComponent;
	class UCStateComponent* StateComponent;

	TArray<FActionDataArray> ActionDataArray;
	FHitData HitData;

protected:
	TArray<uint8> Index;
	TArray<bool> ActionType;

	bool bEnableNext = false;
	bool bNextAction = false;
	EActionType NextActionType;

private:
	TArray<class IIDamageable*> Hitted;
};
