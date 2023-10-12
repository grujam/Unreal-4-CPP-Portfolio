#include "Equipments/CEquipmentStructures.h"
#include "Components/CMovementComponent.h"

void FActionData::Action(ACharacter* InOwnerCharacter)
{
	UCMovementComponent* movementComponent = Cast<UCMovementComponent>(InOwnerCharacter->GetComponentByClass(UCMovementComponent::StaticClass()));

	if (!!movementComponent)
	{
		if (bFixedCamera == true)
			movementComponent->DisableCamera();

		if (bCanMove == false)
			movementComponent->Stop();
	}

	if (!!Montage)
		InOwnerCharacter->PlayAnimMontage(Montage, PlayRate);
}
