#include "Monster/Tasks/CBTTaskNode_Attack.h"
#include "Monster/CMonsterAIController.h"
#include "Components/CMonsterActionComponent.h"
#include "Components/CMonsterStateComponent.h"
#include "Components/CMonsterBehaviorComponent.h"
#include "Monster/CMonster.h"
#include "Monster/Actions/CMonsterAction.h"

UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	NodeName = "Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());


	UCMonsterActionComponent* actionComponent = Cast<UCMonsterActionComponent>(monster->GetComponentByClass(UCMonsterActionComponent::StaticClass()));
	UCMonsterBehaviorComponent* behavior = Cast<UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	if (actionComponent == nullptr)
		return EBTNodeResult::Failed;

	int8 index = Index;

	if(useBlackboardIndex)
	{
		index = behavior->GetAttackIndex();
	}

	ACharacter* target = behavior->GetTarget();

	controller->StopMovement();
	controller->SetFocus(target);
	actionComponent->Action(index);

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());
	UCMonsterStateComponent* stateComponent = Cast<UCMonsterStateComponent>(monster->GetComponentByClass(UCMonsterStateComponent::StaticClass()));
	UCMonsterBehaviorComponent* behavior = Cast<UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	bool bCheck = true;
	bCheck &= stateComponent->IsIdleState();

	if(bCheck)
	{
		controller->K2_ClearFocus();
		behavior->SetWaitMode();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}

EBTNodeResult::Type UCBTTaskNode_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);
	
	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());
	UCMonsterActionComponent* actionComponent = Cast<UCMonsterActionComponent>(monster->GetComponentByClass(UCMonsterActionComponent::StaticClass()));
	UCMonsterBehaviorComponent* behavior = Cast<UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	controller->K2_ClearFocus();
	actionComponent->GetAction()->EndAction();
	behavior->SetWaitMode();

	return EBTNodeResult::Succeeded;
}
