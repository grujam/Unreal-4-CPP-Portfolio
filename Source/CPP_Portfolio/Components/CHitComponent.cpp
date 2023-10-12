#include "Components/CHitComponent.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"

UCHitComponent::UCHitComponent()
{

}

void UCHitComponent::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	HP = MaxHP;

	Super::BeginPlay();

}

void UCHitComponent::Hit(const FHitData& InHitData)
{

}


void UCHitComponent::End_Hit()
{

}

void UCHitComponent::Dead()
{

}

