#include "Monster/Actions/CMonsterAction.h"
#include "Character/Player/CPlayer.h"
#include "Monster/CMonster.h"
#include "Components/CMonsterBehaviorComponent.h"
#include "Components/CMonsterStateComponent.h"
#include "Kismet/KismetMathLibrary.h"

UCMonsterAction::UCMonsterAction()
{
	

}

void UCMonsterAction::BeginPlay(ACMonster* InMonster, TArray<FMonsterAction> InActions)
{
	OwnerMonster = InMonster;
	Actions = InActions;

	MonsterBehaviorComponent = Cast<UCMonsterBehaviorComponent>(OwnerMonster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));
	MonsterStateComponent = Cast<UCMonsterStateComponent>(OwnerMonster->GetComponentByClass(UCMonsterStateComponent::StaticClass()));
}

void UCMonsterAction::Action(uint8 InIndex)
{
	if (InIndex >= Actions.Num())
		return;

	MonsterStateComponent->SetActionState();

	PlayerHitData = Actions[InIndex].PlayerHitData;
	Actions[InIndex].Action(OwnerMonster);
}

void UCMonsterAction::EndAction()
{
	MonsterStateComponent->SetIdleState();
}

void UCMonsterAction::OnCollisionBeginOverlap(UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex,
                                              ACMonster* InAttacker, AActor* InAttackActor, AActor* InOther)
{
	IIDamageable* character = Cast<IIDamageable>(InOther);

	if (character == nullptr)
		return;

	ACPlayer* player = Cast<ACPlayer>(character);
	if (player != nullptr)
	{
		player->TakeDamage(PlayerHitData, OwnerMonster->GetActorLocation());
	}
}

void UCMonsterAction::OnCollisionEndOverlap(ACMonster* InAttacker, AActor* InOther)
{

}
