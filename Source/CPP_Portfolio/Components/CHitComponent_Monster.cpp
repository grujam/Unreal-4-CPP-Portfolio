#include "Components/CHitComponent_Monster.h"
#include "Components/CMonsterStateComponent.h"
#include "Components/CMonsterBehaviorComponent.h"
#include "GameFramework/Character.h"
#include "Widgets/CUserWidget_Damage.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

UCHitComponent_Monster::UCHitComponent_Monster()
{
	FString path = "WidgetBlueprint'/Game/Widgets/WB_Damage.WB_Damage_C'";
	
	DamageWidget = ConstructorHelpers::FClassFinder<UUserWidget>(*path).Class;
}

void UCHitComponent_Monster::BeginPlay()
{
	Super::BeginPlay();
}

void UCHitComponent_Monster::Hit(ACharacter* InAttacker, const FHitData& InHitData, EPhysicalSurface InBodyPart, FHitResult SweepResult)
{
	UCMonsterStateComponent* state = Cast<UCMonsterStateComponent>(OwnerCharacter->GetComponentByClass(UCMonsterStateComponent::StaticClass()));
	UCMonsterBehaviorComponent* behavior = Cast<UCMonsterBehaviorComponent>(OwnerCharacter->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	HP = FMath::Clamp<float>(HP - InHitData.Damage, 0, MaxHP);

	
	APlayerController* controller = Cast<APlayerController>(InAttacker->GetController());

	FVector screenPosition;
	controller->ProjectWorldLocationToScreenWithDistance(OwnerCharacter->GetActorLocation(), screenPosition, true);

	PrintDamage(InAttacker, InHitData.Damage, screenPosition.X, screenPosition.Y, screenPosition.Z);

	if (FMath::IsNearlyZero(HP))
	{
		Dead();
		return;
	}

	//TODO: sound and effects
	if (BodyPartHP.Contains(TEnumAsByte<EPhysicalSurface>(InBodyPart)))
	{
		BodyPartHP[InBodyPart].DamageTaken += InHitData.Damage;

		if (BodyPartHP[InBodyPart].DamageTaken >= BodyPartHP[InBodyPart].BreakDamage)
		{
			BodyPartHP[InBodyPart].DamageTaken -= BodyPartHP[InBodyPart].BreakDamage;

			if (Montages[InBodyPart] != nullptr && BodyPartHP[InBodyPart].BreakCount > 0)
			{
				BodyPartHP[InBodyPart].BreakCount--;

				if (!!state)
				{
					state->SetHitState();
				}

				if(!!behavior)
				{
					behavior->SetHitMode();
				}

				

				OwnerCharacter->PlayAnimMontage(Montages[InBodyPart]);
			}
		}
	}
}

void UCHitComponent_Monster::End_Hit()
{
	UCMonsterStateComponent* state = Cast<UCMonsterStateComponent>(OwnerCharacter->GetComponentByClass(UCMonsterStateComponent::StaticClass()));
	UCMonsterBehaviorComponent* behavior = Cast<UCMonsterBehaviorComponent>(OwnerCharacter->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	state->SetIdleState();
	behavior->SetWaitMode();
}

void UCHitComponent_Monster::Dead()
{
	UCMonsterStateComponent* state = Cast<UCMonsterStateComponent>(OwnerCharacter->GetComponentByClass(UCMonsterStateComponent::StaticClass()));
	UCMonsterBehaviorComponent* behavior = Cast<UCMonsterBehaviorComponent>(OwnerCharacter->GetComponentByClass(UCMonsterBehaviorComponent::StaticClass()));

	state->SetDeadState();
	behavior->SetDeadMode();
}

void UCHitComponent_Monster::PrintDamage(ACharacter* InAttacker, int InDamage, int x, int y, int distance)
{
	APlayerController* controller = Cast<APlayerController>(InAttacker->GetController());

	if (controller == nullptr)
		return;

	UCUserWidget_Damage* widget = Cast<UCUserWidget_Damage>(CreateWidget(controller, DamageWidget));

	distance = FMath::Clamp(distance, 0, 1000);
	float scale = 0.8f + (0.6 * (1 - float(distance) / 1000));

	widget->SetDamage(InDamage);
	widget->SetRenderTranslation(FVector2D(x, y));
	widget->SetRenderScale(FVector2D(scale, scale));
	widget->AddToViewport();
}
