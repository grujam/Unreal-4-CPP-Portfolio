#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CMonsterActionData.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCMonsterActionData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
		class UCMonsterAction* Action;

	UPROPERTY(VisibleAnywhere)
		class ACMonsterCollision* Collision;

public:
	FORCEINLINE class UCMonsterAction* GetMonsterAction() { return Action; }
	FORCEINLINE class ACMonsterCollision* GetMonsterCollision() { return Collision; }
};
