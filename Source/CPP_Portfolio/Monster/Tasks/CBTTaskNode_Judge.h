#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Judge.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCBTTaskNode_Judge : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_Judge();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
