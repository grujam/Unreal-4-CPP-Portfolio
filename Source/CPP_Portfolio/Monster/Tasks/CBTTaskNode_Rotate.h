#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Rotate.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCBTTaskNode_Rotate : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_Rotate();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
