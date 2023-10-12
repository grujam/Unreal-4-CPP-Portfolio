#include "Monster/Service/CBTService_DragonMelee.h"
#include "Monster/CMonsterAIController.h"
#include "Monster/CMonster.h"
#include "Components/CMonsterBehaviorComponent.h"
#include "Components/CMonsterStateComponent.h"

UCBTService_DragonMelee::UCBTService_DragonMelee()
{
	NodeName = "DragonMelee";

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UCBTService_DragonMelee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());
	UCMonsterStateComponent* state = Cast<UCMonsterStateComponent>(monster->GetComponentByClass(UCMonsterStateComponent::StaticClass()));
	UCMonsterBehaviorComponent* behavior = Cast<UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	ACharacter* target = behavior->GetTarget();


	float distance = monster->GetDistanceTo(target);

	if(distance < AttackRange)
	{
		behavior->SetAttackMode();
		return;
	}

	behavior->SetApproachMode();
}
