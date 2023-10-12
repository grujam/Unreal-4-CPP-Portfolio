#include "Monster/Actions/CMonsterActionStructures.h"
#include "Monster/CMonster.h"
#include "Monster/CMonsterAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIController.h"

void FMonsterAction::Action(ACMonster* InMonster)
{
	ACMonsterAIController* controller = Cast<ACMonsterAIController>(InMonster->GetController());
	if (!controller)
		return;

	if(!bFocus)
		controller->ClearFocus(EAIFocusPriority::Gameplay);

	if(!!Montage)
		InMonster->PlayAnimMontage(Montage);
}
