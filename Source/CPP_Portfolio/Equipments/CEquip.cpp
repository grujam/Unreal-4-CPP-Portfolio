#include "Equipments/CEquip.h"

#include "Components/CEquipmentComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"


void UCEquip::BeginPlay(ACharacter* InOwner, const FEquipData& InEquipData, const FEquipData& InUnequipData)
{
	OwnerCharacter = InOwner;
	EquipData = InEquipData;
	UnequipData = InUnequipData;
	
	MovementComponent = Cast<UCMovementComponent>(InOwner->GetComponentByClass(UCMovementComponent::StaticClass()));
	StateComponent = Cast<UCStateComponent>(InOwner->GetComponentByClass(UCStateComponent::StaticClass()));
}

void UCEquip::Equip_Implementation()
{
	StateComponent->SetEquipState();

	if (EquipData.bCanMove == false)
		MovementComponent->Stop();

	if (EquipData.bUseControlRotation)
		MovementComponent->EnableControlRotation();

	if (!!EquipData.Montage)
	{
		OwnerCharacter->PlayAnimMontage(EquipData.Montage, EquipData.PlayRate);
	}
	else
	{
		Begin_Equip();
		End_Equip();
	}
}

void UCEquip::Begin_Equip_Implementation()
{
	bBeginEquip = true;

	if (OnEquipmentBeginEquip.IsBound())
		OnEquipmentBeginEquip.Broadcast();
}

void UCEquip::End_Equip_Implementation()
{
	bBeginEquip = false;
	bEquipped = true;

	MovementComponent->Move();
	StateComponent->SetIdleState();
}

void UCEquip::UnEquip_Implementation()
{
	StateComponent->SetUnequipState();

	if (UnequipData.bCanMove == false)
		MovementComponent->Stop();

	if (UnequipData.bUseControlRotation)
		MovementComponent->EnableControlRotation();

	if (!!UnequipData.Montage)
	{
		OwnerCharacter->PlayAnimMontage(UnequipData.Montage, UnequipData.PlayRate);
	}
	else
	{
		Begin_Unequip();
		End_Unequip();
	}
}

void UCEquip::Begin_Unequip_Implementation()
{
	bBeginUnequip = true;

	if (OnEquipmentUnequip.IsBound())
		OnEquipmentUnequip.Broadcast();
}

void UCEquip::End_Unequip_Implementation()
{
	bBeginUnequip = false;
	bEquipped = false;

	MovementComponent->Move();
	StateComponent->SetIdleState();
}
