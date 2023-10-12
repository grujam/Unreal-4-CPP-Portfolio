#include "Monster/Tasks/CBTTaskNode_Patrol.h"
#include "Monster/CMonster.h"
#include "Monster/CMonsterAIController.h"
#include "Components/CMonsterBehaviorComponent.h"
#include "NavigationSystem.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
	NodeName = "Patrol";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());
	UCMonsterBehaviorComponent* behaviorComponent = Cast<UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	FVector monsterLocation = monster->GetActorLocation();

	UNavigationSystemV1* navSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(monster->GetWorld());

	if (!navSystem)
		return EBTNodeResult::Failed;

	FNavLocation patrolLocation(monsterLocation);

	while(true)
	{
		if (navSystem->GetRandomPointInNavigableRadius(monsterLocation, RandomRadius, patrolLocation))
			break;
	}

	behaviorComponent->SetPatrolLocation(patrolLocation.Location);

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());
	UCMonsterBehaviorComponent* behaviorComponent = Cast<UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	FVector patrolLocation = behaviorComponent->GetPatrolLocation();
	EPathFollowingRequestResult::Type result = controller->MoveToLocation(patrolLocation, AcceptableDistance);

	switch(result)
	{
	case EPathFollowingRequestResult::Failed:
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		break;

	case EPathFollowingRequestResult::AlreadyAtGoal:
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		break;
	}
}
