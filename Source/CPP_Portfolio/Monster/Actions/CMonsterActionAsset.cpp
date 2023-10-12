#include "Monster/Actions/CMonsterActionAsset.h"
#include "Monster/CMonster.h"
#include "CMonsterAction.h"
#include "CMonsterActionData.h"
#include "CMonsterCollision.h"

UCMonsterActionAsset::UCMonsterActionAsset()
{
	ActionClass = UCMonsterAction::StaticClass();
}

void UCMonsterActionAsset::BeginPlay(ACMonster* InOwnerMonster, UCMonsterActionData** InMonsterActionData)
{
	UCMonsterAction* action = nullptr;
	ACMonsterCollision* collision = nullptr;

	if(!!ActionClass)
	{
		action = NewObject<UCMonsterAction>(this, ActionClass);
		action->BeginPlay(InOwnerMonster, Actions);
	}

	if(!!CollisionClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwnerMonster;

		collision = InOwnerMonster->GetWorld()->SpawnActor<ACMonsterCollision>(CollisionClass, params);

		if (!!action)
		{
			collision->OnCollisionBeginOverlap.AddDynamic(action, &UCMonsterAction::OnCollisionBeginOverlap);
			collision->OnCollisionEndOverlap.AddDynamic(action, &UCMonsterAction::OnCollisionEndOverlap);
		}
	}

	*InMonsterActionData = NewObject<UCMonsterActionData>();
	(*InMonsterActionData)->Action = action;
	(*InMonsterActionData)->Collision = collision;
}

