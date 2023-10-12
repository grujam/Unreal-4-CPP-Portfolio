#include "Notifies/CAnimNotify_MEndState.h"

#include "Components/CMonsterActionComponent.h"
#include "Monster/CMonster.h"
#include "Monster/Actions/CMonsterAction.h"

FString UCAnimNotify_MEndState::GetNotifyName_Implementation() const
{
	return "MEndState";
}

void UCAnimNotify_MEndState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr || !MeshComp->GetOwner())
		return;

	ACMonster* monster = Cast<ACMonster>(MeshComp->GetOwner());
	if (monster == nullptr)
		return;

	switch (Type)
	{
	case EMonsterStateType::Action:
		{
			UCMonsterActionComponent* actionComponent = Cast<UCMonsterActionComponent>(monster->GetComponentByClass(UCMonsterActionComponent::StaticClass()));
			actionComponent->GetAction()->EndAction();
		}
		break;
	}
}
