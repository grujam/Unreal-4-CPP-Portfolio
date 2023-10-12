#include "Notifies/CAnimNotifyState_Collision.h"
#include "Components/CEquipmentComponent.h"
#include "Equipments/CEquipment.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCEquipmentComponent* equipmentComponent = Cast<UCEquipmentComponent>(MeshComp->GetOwner()->GetComponentByClass(UCEquipmentComponent::StaticClass()));

	if (!equipmentComponent || !equipmentComponent->GetEquipment())
		return;

	equipmentComponent->GetEquipment()->OnCollisions();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCEquipmentComponent* equipmentComponent = Cast<UCEquipmentComponent>(MeshComp->GetOwner()->GetComponentByClass(UCEquipmentComponent::StaticClass()));

	if (!equipmentComponent || !equipmentComponent->GetEquipment())
		return;

	equipmentComponent->GetEquipment()->OffCollisions();
}
