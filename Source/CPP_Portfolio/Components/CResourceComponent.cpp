#include "Components/CResourceComponent.h"
#include "CMovementComponent.h"
#include "GameFramework/Character.h"

UCResourceComponent::UCResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCResourceComponent::Run()
{
	StaminaRecoverRate = -0.15f;
}

void UCResourceComponent::Walk()
{
	StaminaRecoverRate = 0.1f;

}

void UCResourceComponent::UseStamina(float InCost)
{
	Stamina += InCost;
	Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
}

void UCResourceComponent::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	MovementComponent = Cast<UCMovementComponent>(OwnerCharacter->GetComponentByClass(UCMovementComponent::StaticClass()));
	Stamina = MaxStamina;

	Super::BeginPlay();
}


void UCResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (bRecoverStamina)
	{
		Stamina += StaminaRecoverRate;
		Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
	}

	if(FMath::IsNearlyZero(Stamina))
	{
		Walk();
		MovementComponent->OffDash();
	}
}

