#include "Monster/Service/CBTService_Wolf.h"
#include "Monster/CMonsterAIController.h"
#include "Monster/CMonster.h"
#include "Components/CMonsterStateComponent.h"
#include "Components/CMonsterBehaviorComponent.h"

UCBTService_Wolf::UCBTService_Wolf()
{
	NodeName = "WolfService";

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UCBTService_Wolf::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());
	UCMonsterStateComponent* state = Cast<UCMonsterStateComponent>(monster->GetComponentByClass(UCMonsterStateComponent::StaticClass()));
	UCMonsterBehaviorComponent* behavior = Cast<UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	ACharacter* target = behavior->GetTarget();
	if (target == nullptr)
	{
		behavior->SetPatrolMode();
		return;
	}

	float distance = monster->GetDistanceTo(target);

	if (distance < ActionRange)
	{
		behavior->SetAttackMode();
		return;
	}

	behavior->SetApproachMode();
}
