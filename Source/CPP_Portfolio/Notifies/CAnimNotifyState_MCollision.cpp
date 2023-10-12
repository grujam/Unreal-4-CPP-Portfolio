#include "Notifies/CAnimNotifyState_MCollision.h"
#include "Components/CMonsterActionComponent.h"
#include "Monster/Actions/CMonsterActionData.h"
#include "Monster/Actions/CMonsterCollision.h"

FString UCAnimNotifyState_MCollision::GetNotifyName_Implementation() const
{
	return "MonsterCollision";
}

void UCAnimNotifyState_MCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCMonsterActionComponent* monsterActionComponent = Cast<UCMonsterActionComponent>(MeshComp->GetOwner()->GetComponentByClass(UCMonsterActionComponent::StaticClass()));

	if (!monsterActionComponent || !monsterActionComponent->MonsterActionData->GetMonsterCollision())
		return;

	if(bAllCollision)
		monsterActionComponent->MonsterActionData->GetMonsterCollision()->OnCollisions();
	else
		monsterActionComponent->MonsterActionData->GetMonsterCollision()->OnCollision(CollisionName);
}

void UCAnimNotifyState_MCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	UCMonsterActionComponent* monsterActionComponent = Cast<UCMonsterActionComponent>(MeshComp->GetOwner()->GetComponentByClass(UCMonsterActionComponent::StaticClass()));

	if (!monsterActionComponent || !monsterActionComponent->MonsterActionData->GetMonsterCollision())
		return;

	if (bAllCollision)
		monsterActionComponent->MonsterActionData->GetMonsterCollision()->OffCollisions();
	else
		monsterActionComponent->MonsterActionData->GetMonsterCollision()->OffCollision(CollisionName);
}
