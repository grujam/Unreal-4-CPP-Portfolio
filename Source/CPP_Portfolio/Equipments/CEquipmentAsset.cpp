#include "Equipments/CEquipmentAsset.h"
#include "CActions.h"
#include "CEquipment.h"
#include "CEquip.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"
#include "Equipments/CEquipmentData.h"


UCEquipmentAsset::UCEquipmentAsset()
{
	EquipmentClass = ACEquipment::StaticClass();
	EquipClass = UCEquip::StaticClass();
	ActionClass = UCActions::StaticClass();
}

void UCEquipmentAsset::BeginPlay(ACharacter* InOwner, UCEquipmentData** InEquipmentData)
{
	ACEquipment* equipment = nullptr;
	UCEquip* equip = nullptr;
	UCActions* action = nullptr;

	if (!!EquipmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		equipment = InOwner->GetWorld()->SpawnActor<ACEquipment>(EquipmentClass, params);
	}

	if (!!EquipClass)
	{
		equip = NewObject<UCEquip>(this, EquipClass);
		equip->BeginPlay(InOwner, EquipData, UnequipData);

		if(!!equipment)
		{
			equip->OnEquipmentBeginEquip.AddDynamic(equipment, &ACEquipment::OnBeginEquip);
			equip->OnEquipmentUnequip.AddDynamic(equipment, &ACEquipment::OnUnequip);
		}
	}

	if(!!ActionClass)
	{
		action = NewObject<UCActions>(this, ActionClass);
		action->BeginPlay(equipment, equip, InOwner, ActionDataArrays);

		if(!!equipment)
		{
			equipment->OnEquipmentBeginOverlap.AddDynamic(action, &UCActions::OnEquipmentBeginOverlap);
			equipment->OnEquipmentEndOverlap.AddDynamic(action, &UCActions::OnEquipmentEndOverlap);
			equipment->OnEquipmentOnCollision.AddDynamic(action, &UCActions::OnEquipmentOnCollision);
			equipment->OnEquipmentOffCollision.AddDynamic(action, &UCActions::OnEquipmentEndCollision);
		}
	}

	*InEquipmentData = NewObject<UCEquipmentData>();
	(*InEquipmentData)->Equipment = equipment;
	(*InEquipmentData)->Equip = equip;
	(*InEquipmentData)->Action = action;

	//	/*if (!!Attachment)
	//	{
	//		Equipment->OnEquipmentBeginEquip.AddDynamic(Attachment, &ACAttachment::OnBeginEquip);
	//		Equipment->OnEquipmentUnequip.AddDynamic(Attachment, &ACAttachment::OnUnEquip);
	//	}*/
	//}

	//if (!!ActionClass)
	//{
	//	Action = NewObject<UCDoAction>(this, DoActionClass);
	//	Action->BeginPlay(Equipment, Equip, InOwner, DoActionDatas, HitDatas);

	//	//if (!!Attachment)
	//	//{
	//	//	Attachment->OnAttachmentBeginCollision.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginCollision);
	//	//	Attachment->OnAttachmentEndCollision.AddDynamic(DoAction, &UCDoAction::OnAttachmentEndCollision);

	//	//	Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginOverlap);
	//	//	Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentEndOverlap);
	//	//}
	//}
}
