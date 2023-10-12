#include "Monster/CMonster.h"
#include "Components/CEquipmentComponent.h"
#include "Components/CHitComponent_Monster.h"
#include "Components/CMonsterActionComponent.h"
#include "Components/CMonsterBehaviorComponent.h"
#include "Components/CMonsterStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/CStateComponent.h"

ACMonster::ACMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = this->CreateDefaultSubobject<UCMovementComponent>("Movement Component");
	StateComponent = this->CreateDefaultSubobject<UCMonsterStateComponent>("Monster State Component");
	ActionComponent = this->CreateDefaultSubobject<UCMonsterActionComponent>("Monster Action Component");
	HitComponent = this->CreateDefaultSubobject<UCHitComponent_Monster>("Hit Component");
	BehaviorComponent = this->CreateDefaultSubobject<UCMonsterBehaviorComponent>("Behavior Component");
}

void ACMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACMonster::TakeDamage(ACharacter* InAttacker, const FHitData& InHitData, const EPhysicalSurface InBodyPart, FHitResult SweepResult)
{
	IIDamageable::TakeDamage(InAttacker, InHitData, InBodyPart, SweepResult);

	HitComponent->Hit(InAttacker, InHitData, InBodyPart, SweepResult);
}
