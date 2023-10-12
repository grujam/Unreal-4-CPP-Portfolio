#include "Character/Interface/IDamageable.h"

void IIDamageable::TakeDamage(ACharacter* InAttacker, const FHitData& InHitData, const EPhysicalSurface InBodyPart, FHitResult SweepResult)
{

}

void IIDamageable::TakeDamage(const FPlayerHitData& InHitData, const FVector InAttackerLocation)
{

}
