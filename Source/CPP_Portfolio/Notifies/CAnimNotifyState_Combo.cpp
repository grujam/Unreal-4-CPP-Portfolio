#include "Notifies/CAnimNotifyState_Combo.h"
#include "Components/CEquipmentComponent.h"
#include "Equipments/CActions.h"

FString UCAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UCAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCEquipmentComponent* EquipmentComponent = Cast<UCEquipmentComponent>(MeshComp->GetOwner()->GetComponentByClass(UCEquipmentComponent::StaticClass()));

	if (!EquipmentComponent || !EquipmentComponent->GetActions())
		return;

	EquipmentComponent->GetActions()->EnableNextAction();
}

void UCAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCEquipmentComponent* EquipmentComponent = Cast<UCEquipmentComponent>(MeshComp->GetOwner()->GetComponentByClass(UCEquipmentComponent::StaticClass()));

	if (!EquipmentComponent || !EquipmentComponent->GetActions())
		return;

	EquipmentComponent->GetActions()->DisableNextAction();
}
