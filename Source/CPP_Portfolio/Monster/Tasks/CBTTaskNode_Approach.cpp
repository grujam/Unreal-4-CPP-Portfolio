#include "Monster/Tasks/CBTTaskNode_Approach.h"
#include "Monster/CMonsterAIController.h"
#include "Monster/CMonster.h"
#include "Components/CMonsterBehaviorComponent.h"
#include "Components/CMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UCBTTaskNode_Approach::UCBTTaskNode_Approach()
{
	NodeName = "Approach";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Approach::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());
	UCMonsterBehaviorComponent* behavior = Cast< UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));
	UCMovementComponent* movement = Cast<UCMovementComponent>(monster->GetComponentByClass(UCMovementComponent::StaticClass()));

	ACharacter* target = behavior->GetTarget();

	movement->ChangeSpeed(ESpeed::Run);

	if(target != nullptr)
		controller->MoveToActor(target);

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Approach::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());
	UCMonsterBehaviorComponent* behavior = Cast< UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	ACharacter* target = behavior->GetTarget();

	if (target == nullptr)
		return;

	FRotator view = UKismetMathLibrary::FindLookAtRotation(monster->GetActorLocation(), target->GetActorLocation());
	FRotator rotator = UKismetMathLibrary::RInterpTo(monster->GetActorRotation(), view, DeltaSeconds, 2);

	monster->SetActorRotation(rotator);


	if(behavior->IsApproachMode() == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type UCBTTaskNode_Approach::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	ACMonsterAIController* controller = Cast<ACMonsterAIController>(OwnerComp.GetOwner());
	ACMonster* monster = Cast<ACMonster>(controller->GetPawn());
	UCMonsterBehaviorComponent* behavior = Cast< UCMonsterBehaviorComponent>(monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	return EBTNodeResult::Succeeded;
}
