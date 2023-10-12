#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Attack.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCBTTaskNode_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_Attack();

public:
	UPROPERTY(EditAnywhere)
		uint8 Index;

	UPROPERTY(EditAnywhere)
		bool useBlackboardIndex;

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
