#include "Notifies/CAnimNotify_BeginAction.h"
#include "Components/CEquipmentComponent.h"
#include "Equipments/CActions.h"

FString UCAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return "Begin_Action";
}

void UCAnimNotify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCEquipmentComponent* EquipmentComponent = Cast<UCEquipmentComponent>(MeshComp->GetOwner()->GetComponentByClass(UCEquipmentComponent::StaticClass()));

	if (!EquipmentComponent || !EquipmentComponent->GetActions())
		return;

	EquipmentComponent->GetActions()->Begin_Action();
}
