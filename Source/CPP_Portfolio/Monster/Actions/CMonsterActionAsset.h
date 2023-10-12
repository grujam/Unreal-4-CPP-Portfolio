#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Monster/Actions/CMonsterActionStructures.h"
#include "CMonsterActionAsset.generated.h"

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCMonsterActionAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UCMonsterActionAsset();

public:
	void BeginPlay(class ACMonster* InOwnerMonster, class UCMonsterActionData** InMonsterActionData);

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCMonsterAction> ActionClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACMonsterCollision> CollisionClass;

	UPROPERTY(EditAnywhere)
		TArray<FMonsterAction> Actions;

	UPROPERTY(EditAnywhere)
		TMap<FString, TSubclassOf<class AActor>> Skills;
};
