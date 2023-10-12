#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Wolf.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCBTService_Wolf : public UBTService
{
	GENERATED_BODY()

public:
	UCBTService_Wolf();

public:
	UPROPERTY(EditAnywhere)
		float ActionRange = 150;

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
