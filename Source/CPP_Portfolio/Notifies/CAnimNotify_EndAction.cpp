#include "Notifies/CAnimNotify_EndAction.h"
#include "Components/CEquipmentComponent.h"
#include "Equipments/CActions.h"

FString UCAnimNotify_EndAction::GetNotifyName_Implementation() const
{
	return "End_Action";
}

void UCAnimNotify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCEquipmentComponent* EquipmentComponent = Cast<UCEquipmentComponent>(MeshComp->GetOwner()->GetComponentByClass(UCEquipmentComponent::StaticClass()));

	if (!EquipmentComponent || !EquipmentComponent->GetActions())
		return;

	EquipmentComponent->GetActions()->End_Action();
}
