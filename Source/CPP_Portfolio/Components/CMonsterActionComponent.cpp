#include "Components/CMonsterActionComponent.h"

#include "CMonsterStateComponent.h"
#include "Monster/Actions/CMonsterActionAsset.h"
#include "Monster/CMonster.h"
#include "Monster/Actions/CMonsterAction.h"
#include "Monster/Actions/CMonsterActionData.h"

UCMonsterActionComponent::UCMonsterActionComponent()
{
}


void UCMonsterActionComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerMonster = Cast<ACMonster>(GetOwner());
	MonsterStateComponent = Cast<UCMonsterStateComponent>(OwnerMonster->GetComponentByClass(UCMonsterStateComponent::StaticClass()));

	if(!!MonsterActionAsset)
		MonsterActionAsset->BeginPlay(OwnerMonster, &MonsterActionData);
}

void UCMonsterActionComponent::Action(uint8 InIndex)
{
	if (MonsterStateComponent->IsIdleState() == false)
		return;

	UCMonsterAction* action = MonsterActionData->GetMonsterAction();

	if(!!action)
		action->Action(InIndex);
}

UCMonsterAction* UCMonsterActionComponent::GetAction()
{
	return MonsterActionData->GetMonsterAction();
}

TSubclassOf<AActor> UCMonsterActionComponent::GetSkillClass(FString InSkillName)
{
	return MonsterActionAsset->Skills[InSkillName];
}


