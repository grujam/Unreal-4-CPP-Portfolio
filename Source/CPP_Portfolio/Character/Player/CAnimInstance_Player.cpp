#include "Character/Player/CAnimInstance_Player.h"

#include "GameFramework/Character.h"

void UCAnimInstance_Player::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	EquipmentComponent = Cast<UCEquipmentComponent>(OwnerCharacter->GetComponentByClass(UCEquipmentComponent::StaticClass()));
	if(!!EquipmentComponent)
		EquipmentComponent->OnEquipmentTypeChanged.AddDynamic(this, &UCAnimInstance_Player::OnEquipmentTypeChanged);
}

void UCAnimInstance_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UCAnimInstance_Player::OnEquipmentTypeChanged(EEquipmentType InPrevType, EEquipmentType InNewType)
{
	EquipmentType = InNewType;
}
