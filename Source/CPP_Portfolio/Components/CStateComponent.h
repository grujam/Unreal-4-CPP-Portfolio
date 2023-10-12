#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Equip, Unequip, Action, Hitted, Ride, Dodge, Dead, Down, Counter, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE bool IsIdleState() { return Type == EStateType::Idle; }
	FORCEINLINE bool IsEquipState() { return Type == EStateType::Equip; }
	FORCEINLINE bool IsUnequipState() { return Type == EStateType::Unequip; }
	FORCEINLINE bool IsActionState() { return Type == EStateType::Action; }
	FORCEINLINE bool IsHittedState() { return Type == EStateType::Hitted; }
	FORCEINLINE bool IsRideState() { return Type == EStateType::Ride; }
	FORCEINLINE bool IsDodgeState() { return Type == EStateType::Dodge; }
	FORCEINLINE bool IsDeadState() { return Type == EStateType::Dead; }
	FORCEINLINE bool IsDownState() { return Type == EStateType::Down; }

public:
	void SetIdleState();
	void SetEquipState();
	void SetUnequipState();
	void SetActionState();
	void SetHittedState();
	void SetRideState();
	void SetDodgeState();
	void SetDeadState();
	void SetDownState();

	void EndDownState();

public:
	void Start_State(EStateType InType);
	void End_State(EStateType InType);

private:
	void ChangeType(EStateType InType);

public:
	FStateTypeChanged OnStateTypeChanged;

private:
	EStateType Type = EStateType::Idle;
	class ACharacter* Owner;
};
