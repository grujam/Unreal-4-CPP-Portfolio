#include "Notifies/CAnimNotify_MonsterSkill.h"
#include "Monster/CMonster.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CMonsterActionComponent.h"

FString UCAnimNotify_MonsterSkill::GetNotifyName_Implementation() const
{
	return "MonsterSkill";
}

void UCAnimNotify_MonsterSkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
		return;

	ACMonster* monster = Cast<ACMonster>(MeshComp->GetOwner());

	if (monster == nullptr)
		return;

	UCMonsterActionComponent* action = Cast<UCMonsterActionComponent>(monster->GetComponentByClass(UCMonsterActionComponent::StaticClass()));

	if (action == nullptr)
		return;

	FVector location = monster->GetMesh()->GetSocketLocation(SocketName);
	FRotator rotator = monster->GetActorRotation();

	FActorSpawnParameters params;
	params.Owner = monster;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TSubclassOf<AActor> skill = action->GetSkillClass(SkillName);
	
	AActor* spawnedSkill = monster->GetWorld()->SpawnActor<AActor>(skill, location, rotator, params);

	if (AttachToSocket)
		spawnedSkill->AttachToComponent(monster->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, SocketName);
}
