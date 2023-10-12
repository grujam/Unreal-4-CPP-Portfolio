#include "Monster/Tasks/CBTTaskNode_Judge.h"
#include "Components/CMonsterBehaviorComponent.h"
#include "Monster/CMonsterAIController.h"
#include "Monster/CMonster.h"
#include "Kismet/KismetMathLibrary.h"

UCBTTaskNode_Judge::UCBTTaskNode_Judge()
{
	NodeName = "Judge";

	bNotifyTick = false;
}

EBTNodeResult::Type UCBTTaskNode_Judge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());
	UCMonsterBehaviorComponent* behaviorComponent = Cast<UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	ACharacter* target = behaviorComponent->GetTarget();

	if (!target)
		return EBTNodeResult::Failed;

	int8 index = FMath::RandRange(0, 10);

	if(index < 9)
	{
		behaviorComponent->SetAttackIndex(index);
		behaviorComponent->SetMelee(true);
	}
	else
	{
		behaviorComponent->SetAttackIndex(index);
		behaviorComponent->SetMelee(false);
	}

	behaviorComponent->SetJudgeMode();
	return EBTNodeResult::Succeeded;
}
