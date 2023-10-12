#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CMonsterAIController.generated.h"

UCLASS(Abstract)
class CPP_PORTFOLIO_API ACMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACMonsterAIController();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
		class UAIPerceptionComponent* Perception;

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:
	UFUNCTION()
		virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

protected:
	class ACMonster* Monster;
	class UCMonsterBehaviorComponent* BehaviorComponent;
	class UAISenseConfig_Sight* Sight;
};
