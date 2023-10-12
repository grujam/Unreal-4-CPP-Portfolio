#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMonsterStateComponent.generated.h"

UENUM(BlueprintType)
enum class EMonsterStateType : uint8
{
	Idle, Action, Hit, Dead, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMonsterStateTypeChanged, EMonsterStateType, InPrevType, EMonsterStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCMonsterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMonsterStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE bool IsIdleState() { return Type == EMonsterStateType::Idle; }
	FORCEINLINE bool IsActionState() { return Type == EMonsterStateType::Action; }
	FORCEINLINE bool IsHitState() { return Type == EMonsterStateType::Hit; }
	FORCEINLINE bool IsDeadState() { return Type == EMonsterStateType::Dead; }

public:
	void SetIdleState();
	void SetActionState();
	void SetHitState();
	void SetDeadState();

private:
	void ChangeType(EMonsterStateType InType);

public:
	FMonsterStateTypeChanged OnMonsterStateTypeChanged;

private:
	EMonsterStateType Type = EMonsterStateType::Idle;
};
