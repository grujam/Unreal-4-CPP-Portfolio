#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Equipments/CEquipmentStructures.h"
#include "Monster/Actions/CMonsterActionStructures.h"
#include "IDamageable.generated.h"

UINTERFACE(MinimalAPI)
class UIDamageable : public UInterface
{
	GENERATED_BODY()
};

class CPP_PORTFOLIO_API IIDamageable
{
	GENERATED_BODY()

public:
	virtual void TakeDamage(ACharacter* InAttacker, const FHitData& InHitData, const EPhysicalSurface InBodyPart, FHitResult SweepResult);
	virtual void TakeDamage(const FPlayerHitData& InHitData, const FVector InAttackerLocation);
};
