#include "Notifies/CAnimNotifyState_Equip.h"
#include "Components/CEquipmentComponent.h"
#include "Equipments/CEquip.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCEquipmentComponent* EquipmentComponent = Cast<UCEquipmentComponent>(MeshComp->GetOwner()->GetComponentByClass(UCEquipmentComponent::StaticClass()));
	if (!EquipmentComponent || !EquipmentComponent->GetEquip())
		return;

	EquipmentComponent->GetEquip()->Begin_Equip();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCEquipmentComponent* EquipmentComponent = Cast<UCEquipmentComponent>(MeshComp->GetOwner()->GetComponentByClass(UCEquipmentComponent::StaticClass()));
	if (!EquipmentComponent || !EquipmentComponent->GetEquip())
		return;

	EquipmentComponent->GetEquip()->End_Equip();
}
