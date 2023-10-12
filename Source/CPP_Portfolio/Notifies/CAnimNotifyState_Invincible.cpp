#include "Notifies/CAnimNotifyState_Invincible.h"
#include "Components/CHitComponent_Player.h"

FString UCAnimNotifyState_Invincible::GetNotifyName_Implementation() const
{
	return "Invincible";
}

void UCAnimNotifyState_Invincible::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (!MeshComp || MeshComp->GetOwner() == nullptr)
		return;

	UCHitComponent_Player* hit = Cast<UCHitComponent_Player>(MeshComp->GetOwner()->GetComponentByClass(UCHitComponent_Player::StaticClass()));

	if (hit == nullptr)
		return;

	hit->SetInvincibility(true);
}

void UCAnimNotifyState_Invincible::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (!MeshComp || MeshComp->GetOwner() == nullptr)
		return;

	UCHitComponent_Player* hit = Cast<UCHitComponent_Player>(MeshComp->GetOwner()->GetComponentByClass(UCHitComponent_Player::StaticClass()));

	if (hit == nullptr)
		return;

	hit->SetInvincibility(false);
}
