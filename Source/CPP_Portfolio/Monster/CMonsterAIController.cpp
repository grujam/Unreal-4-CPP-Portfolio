#include "Monster/CMonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACMonsterAIController::ACMonsterAIController()
{
	
}

void ACMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ACMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACMonsterAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{

}
