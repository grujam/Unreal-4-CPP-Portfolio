#include "Components/CMonsterStateComponent.h"

UCMonsterStateComponent::UCMonsterStateComponent()
{
}

void UCMonsterStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCMonsterStateComponent::SetIdleState()
{
	ChangeType(EMonsterStateType::Idle);
}

void UCMonsterStateComponent::SetActionState()
{
	ChangeType(EMonsterStateType::Action);
}

void UCMonsterStateComponent::SetHitState()
{
	ChangeType(EMonsterStateType::Hit);
}

void UCMonsterStateComponent::SetDeadState()
{
	ChangeType(EMonsterStateType::Dead);
}

void UCMonsterStateComponent::ChangeType(EMonsterStateType InType)
{
	EMonsterStateType prevType = Type;
	Type = InType;

	if (OnMonsterStateTypeChanged.IsBound())
		OnMonsterStateTypeChanged.Broadcast(prevType, Type);
}

