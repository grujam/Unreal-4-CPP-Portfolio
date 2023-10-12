#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_DragonMelee.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCBTService_DragonMelee : public UBTService
{
	GENERATED_BODY()

public:
	UCBTService_DragonMelee();

public:
	UPROPERTY(EditAnywhere)
		float AttackRange = 500;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
