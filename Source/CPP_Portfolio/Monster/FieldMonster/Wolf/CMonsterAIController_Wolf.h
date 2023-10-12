#pragma once

#include "CoreMinimal.h"
#include "Monster/CMonsterAIController.h"
#include "CMonsterAIController_Wolf.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACMonsterAIController_Wolf : public ACMonsterAIController
{
	GENERATED_BODY()

public:
	ACMonsterAIController_Wolf();

public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;


protected:
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;
};
