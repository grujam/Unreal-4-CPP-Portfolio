#include "Monster/Dragon/CAnimInstance_Dragon.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance_Dragon::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(!!OwnerCharacter)
		bFlying = OwnerCharacter->GetCharacterMovement()->IsFlying();
}
