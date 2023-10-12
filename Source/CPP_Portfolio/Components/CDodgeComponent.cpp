#include "Components/CDodgeComponent.h"
#include "Components/CEquipmentComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CResourceComponent.h"
#include "Components/CHitComponent_Player.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UCDodgeComponent::UCDodgeComponent()
{
}


void UCDodgeComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCDodgeComponent::Dodge()
{
	UCEquipmentComponent* equipmentComponent = Cast<UCEquipmentComponent>(OwnerCharacter->GetComponentByClass(UCEquipmentComponent::StaticClass()));
	UCStateComponent* stateComponent = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));
	UCResourceComponent* resourceComponent = Cast<UCResourceComponent>(OwnerCharacter->GetComponentByClass(UCResourceComponent::StaticClass()));
	UCHitComponent_Player* hitComponent = Cast<UCHitComponent_Player>(OwnerCharacter->GetComponentByClass(UCHitComponent_Player::StaticClass()));

	//idle상태가 아니거나 구르기 동작이 없는 경우
	if (stateComponent->IsIdleState() == false || Dodges.Contains(equipmentComponent->GetType()) == false )
		return;

	//무기를 들고 있지 않는 경우 구르지 못함
	if (equipmentComponent->GetType() == EEquipmentType::Unarmed)
		return;

	FDodgeData dodge = Dodges[equipmentComponent->GetType()];

	// 스태미나 부족
	if (resourceComponent->Stamina < dodge.StaminaCost)
		return;

	//구르기 무적
	if (hitComponent != nullptr)
		hitComponent->SetInvincibility(true);

	FVector v1 = OwnerCharacter->GetActorForwardVector();
	FVector v2 = OwnerCharacter->GetLastMovementInputVector();

	// 속도가 100 이상인 경우 앞으로 구르기 모션
	if(OwnerCharacter->GetCharacterMovement()->Velocity.Size() >= 100.0f)
	{
		FRotator rotator = v2.ToOrientationRotator();
		OwnerCharacter->SetActorRotation(rotator);

		OwnerCharacter->PlayAnimMontage(dodge.Montages[(uint8)ESides::Front]);

		resourceComponent->SetRecoverStamina(false);
		resourceComponent->UseStamina(-dodge.StaminaCost);
		stateComponent->SetDodgeState();

		return;
	}

	float dot = UKismetMathLibrary::Dot_VectorVector(v1, v2);
	float degree = UKismetMathLibrary::DegAcos(dot);

	//속도가 100 미만인 경우 각 방향 구르기 모션
	if(degree > 135)
	{
		if(!!dodge.Montages[(uint8)ESides::Back])
		{
			OwnerCharacter->PlayAnimMontage(dodge.Montages[(uint8)ESides::Back]);
		}
	}
	else if(degree < 45)
	{
		if (!!dodge.Montages[(uint8)ESides::Front])
		{
			OwnerCharacter->PlayAnimMontage(dodge.Montages[(uint8)ESides::Front]);
		}
	}
	else
	{
		FVector cross = UKismetMathLibrary::Cross_VectorVector(v2, v1);

		if(cross.Z >= 0)
		{
			if (!!dodge.Montages[(uint8)ESides::Left])
			{
				OwnerCharacter->PlayAnimMontage(dodge.Montages[(uint8)ESides::Left]);
			}
		}
		else
		{
			if (!!dodge.Montages[(uint8)ESides::Right])
			{
				OwnerCharacter->PlayAnimMontage(dodge.Montages[(uint8)ESides::Right]);
			}
		}
	}

	resourceComponent->SetRecoverStamina(false);
	resourceComponent->UseStamina(-dodge.StaminaCost);
	stateComponent->SetDodgeState();
}

void UCDodgeComponent::End_Dodge()
{
	UCStateComponent* stateComponent = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));
	UCResourceComponent* resourceComponent = Cast<UCResourceComponent>(OwnerCharacter->GetComponentByClass(UCResourceComponent::StaticClass()));
	UCHitComponent_Player* hitComponent = Cast<UCHitComponent_Player>(OwnerCharacter->GetComponentByClass(UCHitComponent_Player::StaticClass()));

	resourceComponent->SetRecoverStamina(true);
	stateComponent->SetIdleState();

	//구르기 무적 해제
	if (hitComponent != nullptr)
		hitComponent->SetInvincibility(false);
}

