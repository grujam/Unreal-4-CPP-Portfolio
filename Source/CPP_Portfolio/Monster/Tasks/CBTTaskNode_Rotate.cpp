#include "Monster/Tasks/CBTTaskNode_Rotate.h"
#include "Monster/CMonster.h"
#include "Monster/CMonsterAIController.h"
#include "Components/CMonsterBehaviorComponent.h"
#include "Kismet/KismetMathLibrary.h"

UCBTTaskNode_Rotate::UCBTTaskNode_Rotate()
{
	NodeName = "Rotate";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Rotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Rotate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());
	UCMonsterBehaviorComponent* behavior = Cast< UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	ACharacter* target = behavior->GetTarget();

	if (!target)
		return;
	FRotator view = UKismetMathLibrary::FindLookAtRotation(monster->GetActorLocation(), target->GetActorLocation());
	FRotator rotator = UKismetMathLibrary::RInterpTo(monster->GetActorRotation(), view, DeltaSeconds, 10);

	monster->SetActorRotation(rotator);

	if (view.Equals(monster->GetActorRotation(), 10))
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	
}