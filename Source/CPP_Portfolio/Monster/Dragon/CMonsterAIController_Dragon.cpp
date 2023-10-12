#include "Monster/Dragon/CMonsterAIController_Dragon.h"
#include "Monster/CMonster.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/CMonsterBehaviorComponent.h"

ACMonsterAIController_Dragon::ACMonsterAIController_Dragon()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());

	Sight->SightRadius = 20000;
	Sight->LoseSightRadius = 100000;
	Sight->PeripheralVisionAngleDegrees = 180;
	Sight->SetMaxAge(10);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
}

void ACMonsterAIController_Dragon::BeginPlay()
{
	Super::BeginPlay();

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACMonsterAIController_Dragon::OnPerceptionUpdated);
}

void ACMonsterAIController_Dragon::OnPossess(APawn* InPawn)
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

void ACMonsterAIController_Dragon::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACMonsterAIController_Dragon::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	Super::OnPerceptionUpdated(UpdatedActors);

	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	if(actors.Num() > 0)
	{
		Blackboard->SetValueAsObject("Target", actors[0]);

		return;
	}
	Blackboard->SetValueAsObject("Target", nullptr);
}
