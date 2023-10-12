#include "Notifies/CAnimNotify_EndState.h"
#include "GameFramework/Character.h"
#include "Components/CHitComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/CDodgeComponent.h"
#include "Components/CStateComponent.h"

FString UCAnimNotify_EndState::GetNotifyName_Implementation() const
{
	return "EndState";
}

void UCAnimNotify_EndState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr || !MeshComp->GetOwner())
		return;

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	if (character == nullptr)
		return;

	UCHitComponent* hitComponent = Cast<UCHitComponent>(character->GetComponentByClass(UCHitComponent::StaticClass()));
	UCMovementComponent* movementComponent = Cast<UCMovementComponent>(character->GetComponentByClass(UCMovementComponent::StaticClass()));
	UCDodgeComponent* dodgeComponent = Cast<UCDodgeComponent>(character->GetComponentByClass(UCDodgeComponent::StaticClass()));
	UCStateComponent* stateComponent = Cast<UCStateComponent>(character->GetComponentByClass(UCStateComponent::StaticClass()));

	if (hitComponent == nullptr || movementComponent == nullptr)
		return;

	switch(Type)
	{
	case EStateType::Hitted: hitComponent->End_Hit(); movementComponent->Move(); break;
	case EStateType::Dodge: dodgeComponent->End_Dodge(); movementComponent->Move(); break;
	case EStateType::Down: stateComponent->End_State(EStateType::Down); break;
	}
}
