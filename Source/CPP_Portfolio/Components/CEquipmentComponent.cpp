#include "Components/CEquipmentComponent.h"
#include "Components/CStateComponent.h"
#include "Equipments/CEquipmentAsset.h"
#include "GameFramework/Character.h"
#include "Equipments/CEquip.h"
#include "Equipments/CActions.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Equipments/CEquipmentData.h"

UCEquipmentComponent::UCEquipmentComponent()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EEquipmentType::Unarmed; i++)
	{
		if (!!EquipmentAsset[i])
			EquipmentAsset[i]->BeginPlay(OwnerCharacter, &EquipmentData[i]);
	}
}


void UCEquipmentComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

ACEquipment* UCEquipmentComponent::GetEquipment()
{
	if (IsUnarmedMode() || !EquipmentData[(int32)Type])
		return nullptr;

	return EquipmentData[(int32)Type]->GetEquipment();
}

UCEquip* UCEquipmentComponent::GetEquip()
{
	if (PrevType != EEquipmentType::Unarmed && !!EquipmentAsset[(int32)PrevType])
		return EquipmentData[(int32)PrevType]->GetEquip();

	if (IsUnarmedMode() || !EquipmentData[(int32)Type])
		return nullptr;

	return EquipmentData[(int32)Type]->GetEquip();
}

UCActions* UCEquipmentComponent::GetActions()
{
	if (IsUnarmedMode() || !EquipmentData[(int32)Type])
		return nullptr;

	return EquipmentData[(int32)Type]->GetActions();
}

void UCEquipmentComponent::SetUnarmedMode()
{
	GetEquip()->UnEquip();

	ChangeType(EEquipmentType::Unarmed);
}

void UCEquipmentComponent::SetLongSwordMode()
{
	if (!IsIdleState())
		return;

	SetMode(EEquipmentType::LongSword);
}

void UCEquipmentComponent::SetDualBladeMode()
{
	if (!IsIdleState())
		return;

	SetMode(EEquipmentType::DualBlade);
}

void UCEquipmentComponent::SetHammerMode()
{
	if (!IsIdleState())
		return;

	SetMode(EEquipmentType::Hammer);
}

void UCEquipmentComponent::SetSpearMode()
{
	if (!IsIdleState())
		return;

	SetMode(EEquipmentType::Spear);
}

void UCEquipmentComponent::SetOHSwordMode()
{
	if (!IsIdleState())
		return;

	SetMode(EEquipmentType::OHSword);
}

void UCEquipmentComponent::SetBowMode()
{
	if (!IsIdleState())
		return;

	SetMode(EEquipmentType::Bow);
}

void UCEquipmentComponent::WaitAction()
{
	FTimerDelegate delegate;
	delegate.BindUObject(this, &UCEquipmentComponent::DoAction);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, delegate, 0.01, false, 0.05);
}

void UCEquipmentComponent::DoAction()
{
	if (IsUnarmedMode())
		return;

	if (bKeyLeft && bKeyRight)
		DoActionDouble();
	else if (bKeyLeft && bKeyExtra)
		DoActionExtraLeft();
	else if (bKeyRight && bKeyExtra)
		DoActionExtraRight();
	else if (bKeyLeft)
		DoActionLeft();
	else if (bKeyRight)
		DoActionRight();
	else if (bKeyExtra)
		DoActionExtra();

	ResetKeys();
}

void UCEquipmentComponent::DoActionLeft()
{
	if (!OwnerCharacter || Type == EEquipmentType::Unarmed)
		return;

	if (!EquipmentData[(int32)Type]->GetActions())
		return;

	EquipmentData[(int32)Type]->GetActions()->Action(EActionType::Left);
}

void UCEquipmentComponent::DoActionRight()
{
	if (!OwnerCharacter || Type == EEquipmentType::Unarmed)
		return;

	if (!EquipmentData[(int32)Type]->GetActions())
		return;

	EquipmentData[(int32)Type]->GetActions()->Action(EActionType::Right);
}

void UCEquipmentComponent::DoActionDouble()
{
	if (!EquipmentData[(int32)Type]->GetActions())
		return;

	EquipmentData[(int32)Type]->GetActions()->Action(EActionType::Double);
}

void UCEquipmentComponent::DoActionExtra()
{
	if (!OwnerCharacter || Type == EEquipmentType::Unarmed)
		return;

	if (!EquipmentData[(int32)Type]->GetActions())
		return;

	EquipmentData[(int32)Type]->GetActions()->Action(EActionType::Extra);
}

void UCEquipmentComponent::DoActionExtraLeft()
{
	if (!EquipmentData[(int32)Type]->GetActions())
		return;

	EquipmentData[(int32)Type]->GetActions()->Action(EActionType::ExtraLeft);
}

void UCEquipmentComponent::DoActionExtraRight()
{
	if (!EquipmentData[(int32)Type]->GetActions())
		return;

	EquipmentData[(int32)Type]->GetActions()->Action(EActionType::ExtraRight);
}

bool UCEquipmentComponent::IsIdleState()
{
	return Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()))->IsIdleState();
}

void UCEquipmentComponent::SetMode(EEquipmentType InType)
{
	if(Type == InType || IsUnarmedMode() == false)
	{
		SetUnarmedMode();

		return;
	}

	if(!!EquipmentData[(int32)InType])
	{
		EquipmentData[(int32)InType]->GetEquip()->Equip();

		ChangeType(InType);
	}
}

void UCEquipmentComponent::ChangeType(EEquipmentType InType)
{
	PrevType = Type;
	Type = InType;

	if (OnEquipmentTypeChanged.IsBound())
		OnEquipmentTypeChanged.Broadcast(PrevType, InType);
}
