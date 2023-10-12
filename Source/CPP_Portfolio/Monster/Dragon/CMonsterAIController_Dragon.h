#pragma once

#include "CoreMinimal.h"
#include "Monster/CMonsterAIController.h"
#include "CMonsterAIController_Dragon.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACMonsterAIController_Dragon : public ACMonsterAIController
{
	GENERATED_BODY()

public:
	ACMonsterAIController_Dragon();

public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:
	virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;
};
