#include "Notifies/CAnimNotifyState_Unequip.h"
#include "Components/CEquipmentComponent.h"
#include "Equipments/CEquip.h"

FString UCAnimNotifyState_Unequip::GetNotifyName_Implementation() const
{
	return "Unequip";
}

void UCAnimNotifyState_Unequip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCEquipmentComponent* EquipmentComponent = Cast<UCEquipmentComponent>(MeshComp->GetOwner()->GetComponentByClass(UCEquipmentComponent::StaticClass()));
	if (!EquipmentComponent || !EquipmentComponent->GetEquip())
		return;

	EquipmentComponent->GetEquip()->Begin_Unequip();
}

void UCAnimNotifyState_Unequip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCEquipmentComponent* EquipmentComponent = Cast<UCEquipmentComponent>(MeshComp->GetOwner()->GetComponentByClass(UCEquipmentComponent::StaticClass()));
	if (!EquipmentComponent || !EquipmentComponent->GetEquip())
		return;

	EquipmentComponent->GetEquip()->End_Unequip();
}
