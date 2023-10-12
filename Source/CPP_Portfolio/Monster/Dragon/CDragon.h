#pragma once

#include "CoreMinimal.h"
#include "Monster/CMonster.h"
#include "CDragon.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACDragon : public ACMonster
{
	GENERATED_BODY()

public:
	ACDragon();

protected:
	virtual void BeginPlay() override;
};
