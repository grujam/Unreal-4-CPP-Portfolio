#include "Components/CHitComponent_Player.h"
#include "CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/CScreenComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Monster/Actions/CMonsterActionStructures.h"

UCHitComponent_Player::UCHitComponent_Player()
{

}

void UCHitComponent_Player::BeginPlay()
{
	Super::BeginPlay();
}

void UCHitComponent_Player::Hit(const FPlayerHitData& InHitData, const FVector InAttackerLocation)
{
	if (bInvincible)
		return;

	UCStateComponent* state = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));

	if (state == nullptr)
		return;

	if (state->IsDownState() || state->IsHittedState())
		return;

	state->SetHittedState();

	HP = FMath::Clamp<float>(HP - InHitData.Damage, 0, MaxHP);

	if (FMath::IsNearlyZero(HP))
	{
		Dead();
		return;
	}

	FVector v1 = OwnerCharacter->GetActorForwardVector();
	FVector v2 = InAttackerLocation - OwnerCharacter->GetActorLocation();

	v2.Normalize();

	v2.Z = 0;

	float dot = UKismetMathLibrary::Dot_VectorVector(v1, v2);
	float degree = UKismetMathLibrary::DegAcos(dot);

	ESides side;

	if (degree > 135)
	{
		side = ESides::Back;
	}
	else if (degree < 45)
	{
		side = ESides::Front;
	}
	else
	{
		FVector cross = UKismetMathLibrary::Cross_VectorVector(v2, v1);
		if (cross.Z >= 0)
			side = ESides::Left;
		else
			side = ESides::Front;
	}

	if(Montages.Contains(InHitData.HitStrength))
	{
		UCMovementComponent* movementComponent = Cast<UCMovementComponent>(OwnerCharacter->GetComponentByClass(UCMovementComponent::StaticClass()));

		FPlayerHitMontage montage = Montages[InHitData.HitStrength];

		movementComponent->Stop();
		if(!!montage.CameraShake)
			Cast<APlayerController>(OwnerCharacter->GetController())->PlayerCameraManager->StartCameraShake(montage.CameraShake, 1.0f);
		OwnerCharacter->PlayAnimMontage(montage.montages[(int32)side]);
		return;
	}

	End_Hit();
}

void UCHitComponent_Player::End_Hit()
{
	UCStateComponent* state = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));
	
	state->SetIdleState();
}

void UCHitComponent_Player::Dead()
{
	UCStateComponent* state = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));
	UCHitComponent_Player* hit = Cast<UCHitComponent_Player>(OwnerCharacter->GetComponentByClass(UCHitComponent_Player::StaticClass()));
	UCScreenComponent* screen = Cast<UCScreenComponent>(OwnerCharacter->GetComponentByClass(UCScreenComponent::StaticClass()));

	int index = FMath::RandRange(0, DeadMontages.Num() - 1);

	if (DeadMontages.Num() <= 0)
		return;

	OwnerCharacter->PlayAnimMontage(DeadMontages[index]);

	screen->ShowEffect(EScreenType::Fade);
	state->SetDeadState();
	hit->SetInvincibility(true);
}
