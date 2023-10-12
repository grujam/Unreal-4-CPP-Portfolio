#include "Components/CStateComponent.h"
#include "Components/CHitComponent_Player.h"
#include "GameFramework/Character.h"

UCStateComponent::UCStateComponent()
{
	Owner = Cast<ACharacter>(GetOwner());
}


void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCStateComponent::SetIdleState()
{
	ChangeType(EStateType::Idle);
}

void UCStateComponent::SetEquipState()
{
	ChangeType(EStateType::Equip);
}

void UCStateComponent::SetUnequipState()
{
	ChangeType(EStateType::Unequip);
}

void UCStateComponent::SetActionState()
{
	ChangeType(EStateType::Action);
}

void UCStateComponent::SetHittedState()
{
	ChangeType(EStateType::Hitted);
}

void UCStateComponent::SetRideState()
{
	ChangeType(EStateType::Ride);
}

void UCStateComponent::SetDodgeState()
{
	ChangeType(EStateType::Dodge);
}

void UCStateComponent::SetDeadState()
{
	ChangeType(EStateType::Dead);
}

void UCStateComponent::SetDownState()
{
	ChangeType(EStateType::Down);
	UCHitComponent_Player* hit = Cast<UCHitComponent_Player>(Owner->GetComponentByClass(UCHitComponent_Player::StaticClass()));
	if (hit->GetDownMontage() == nullptr)
		return;

	Owner->PlayAnimMontage(hit->GetDownMontage());
}

void UCStateComponent::EndDownState()
{
	UCHitComponent_Player* hit = Cast<UCHitComponent_Player>(Owner->GetComponentByClass(UCHitComponent_Player::StaticClass()));

	if (hit->GetStandUpMontage() == nullptr)
		return;
	GLog->Log("UP");
	Owner->PlayAnimMontage(hit->GetStandUpMontage());
}

void UCStateComponent::Start_State(EStateType InType)
{
	switch(InType)
	{
	case EStateType::Down: SetDownState(); break;
	}
}

void UCStateComponent::End_State(EStateType InType)
{
	switch(InType)
	{
	case EStateType::Down: EndDownState(); break;
	}
}


void UCStateComponent::ChangeType(EStateType InType)
{
	EStateType prevType = Type;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prevType, Type);
}


