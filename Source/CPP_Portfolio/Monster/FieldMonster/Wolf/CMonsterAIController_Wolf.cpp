#include "Monster/FieldMonster/Wolf/CMonsterAIController_Wolf.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/CMonster.h"
#include "Components/CMonsterBehaviorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACMonsterAIController_Wolf::ACMonsterAIController_Wolf()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());

	Sight->SightRadius = 600;
	Sight->LoseSightRadius = 2000;
	Sight->PeripheralVisionAngleDegrees = 60;
	Sight->SetMaxAge(2);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
}

void ACMonsterAIController_Wolf::BeginPlay()
{
	Super::BeginPlay();

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACMonsterAIController_Wolf::OnPerceptionUpdated);
}

void ACMonsterAIController_Wolf::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Monster = Cast<ACMonster>(InPawn);
	SetGenericTeamId(Monster->GetTeamID());

	UseBlackboard(Monster->GetBehaviorTree()->BlackboardAsset, Blackboard);

	BehaviorComponent = Cast<UCMonsterBehaviorComponent>(Monster->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));
	BehaviorComponent->SetBlackboard(Blackboard);

	if (Monster->GetBehaviorTree() != nullptr)
		RunBehaviorTree(Monster->GetBehaviorTree());
}

void ACMonsterAIController_Wolf::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACMonsterAIController_Wolf::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	if (actors.Num() > 0)
	{
		Blackboard->SetValueAsObject("Target", actors[0]);

		return;
	}
	Blackboard->SetValueAsObject("Target", nullptr);
}
