#include "Components/CMonsterBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCMonsterBehaviorComponent::UCMonsterBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

EMonsterBehaviorType UCMonsterBehaviorComponent::GetMonsterBehaviorType()
{
	return (EMonsterBehaviorType)Blackboard->GetValueAsEnum(MonsterBehaviorTypeKey);
}

ACharacter* UCMonsterBehaviorComponent::GetTarget()
{
	return (ACharacter*)Blackboard->GetValueAsObject(TargetKey);
}

bool UCMonsterBehaviorComponent::IsWaitMode()
{
	return GetMonsterBehaviorType() == EMonsterBehaviorType::Wait;
}

bool UCMonsterBehaviorComponent::IsApproachMode()
{
	return GetMonsterBehaviorType() == EMonsterBehaviorType::Approach;
}

bool UCMonsterBehaviorComponent::IsAttackMode()
{
	return GetMonsterBehaviorType() == EMonsterBehaviorType::Attack;
}

bool UCMonsterBehaviorComponent::IsHitMode()
{
	return GetMonsterBehaviorType() == EMonsterBehaviorType::Hit;
}

bool UCMonsterBehaviorComponent::IsPatrolMode()
{
	return GetMonsterBehaviorType() == EMonsterBehaviorType::Patrol;
}

bool UCMonsterBehaviorComponent::IsDeadMode()
{
	return GetMonsterBehaviorType() == EMonsterBehaviorType::Dead;
}

bool UCMonsterBehaviorComponent::IsRestMode()
{
	return GetMonsterBehaviorType() == EMonsterBehaviorType::Rest;
}

bool UCMonsterBehaviorComponent::IsSleepMode()
{
	return GetMonsterBehaviorType() == EMonsterBehaviorType::Sleep;
}

bool UCMonsterBehaviorComponent::IsJudgeMode()
{
	return GetMonsterBehaviorType() == EMonsterBehaviorType::Judge;
}

void UCMonsterBehaviorComponent::SetWaitMode()
{
	ChangeMonsterBehaviorType(EMonsterBehaviorType::Wait);
}

void UCMonsterBehaviorComponent::SetApproachMode()
{
	ChangeMonsterBehaviorType(EMonsterBehaviorType::Approach);
}

void UCMonsterBehaviorComponent::SetAttackMode()
{
	ChangeMonsterBehaviorType(EMonsterBehaviorType::Attack);
}

void UCMonsterBehaviorComponent::SetHitMode()
{
	ChangeMonsterBehaviorType(EMonsterBehaviorType::Hit);
}

void UCMonsterBehaviorComponent::SetPatrolMode()
{
	ChangeMonsterBehaviorType(EMonsterBehaviorType::Patrol);
}

void UCMonsterBehaviorComponent::SetDeadMode()
{
	ChangeMonsterBehaviorType(EMonsterBehaviorType::Dead);
}

void UCMonsterBehaviorComponent::SetRestMode()
{
	ChangeMonsterBehaviorType(EMonsterBehaviorType::Rest);
}

void UCMonsterBehaviorComponent::SetSleepMode()
{
	ChangeMonsterBehaviorType(EMonsterBehaviorType::Sleep);
}

void UCMonsterBehaviorComponent::SetJudgeMode()
{
	ChangeMonsterBehaviorType(EMonsterBehaviorType::Judge);
}

void UCMonsterBehaviorComponent::SetPatrolLocation(FVector InPatrolLocation)
{
	Blackboard->SetValueAsVector(PatrolLocationKey, InPatrolLocation);
}

FVector UCMonsterBehaviorComponent::GetPatrolLocation()
{
	return Blackboard->GetValueAsVector(PatrolLocationKey);
}

void UCMonsterBehaviorComponent::SetMelee(bool InBool)
{
	Blackboard->SetValueAsBool(MeleeKey, InBool);
}

bool UCMonsterBehaviorComponent::GetMelee()
{
	return Blackboard->GetValueAsBool(MeleeKey);
}

void UCMonsterBehaviorComponent::SetAttackIndex(int8 InIndex)
{
	Blackboard->SetValueAsInt(AttackIndexKey, InIndex);
}

int8 UCMonsterBehaviorComponent::GetAttackIndex()
{
	return Blackboard->GetValueAsInt(AttackIndexKey);
}

void UCMonsterBehaviorComponent::ChangeMonsterBehaviorType(EMonsterBehaviorType InMonsterBehaviorType)
{
	EMonsterBehaviorType prevType = GetMonsterBehaviorType();

	Blackboard->SetValueAsEnum(MonsterBehaviorTypeKey, (uint8)InMonsterBehaviorType);
}

void UCMonsterBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCMonsterBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

