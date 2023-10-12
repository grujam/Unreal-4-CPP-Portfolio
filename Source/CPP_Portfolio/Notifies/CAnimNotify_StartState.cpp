#include "Notifies/CAnimNotify_StartState.h"
#include "Character/Player/CPlayer.h"
#include "Components/CStateComponent.h"

FString UCAnimNotify_StartState::GetNotifyName_Implementation() const
{
	return "StartState";
}

void UCAnimNotify_StartState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
		return;

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());

	if (player == nullptr)
		return;

	UCStateComponent* state = Cast<UCStateComponent>(player->GetComponentByClass(UCStateComponent::StaticClass()));

	if (state == nullptr)
		return;

	state->Start_State(Type);
}
