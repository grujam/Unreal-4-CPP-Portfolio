#pragma once

#include "CoreMinimal.h"
#include "Components/CHitComponent.h"
#include "CHitComponent_Monster.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP_PORTFOLIO_API UCHitComponent_Monster : public UCHitComponent
{
	GENERATED_BODY()
public:
	UCHitComponent_Monster();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		TMap<TEnumAsByte<EPhysicalSurface>, FBodyDamage> BodyPartHP;

	UPROPERTY(EditDefaultsOnly, Category = "Hit Montages")
		TMap<TEnumAsByte<EPhysicalSurface>, UAnimMontage*> Montages;

	UPROPERTY(EditDefaultsOnly, Category = "Hit Montages")
		UAnimMontage* DeadMontage;

	UPROPERTY(VisibleAnywhere, Category = "Damage Visibility")
		TSubclassOf<class UUserWidget> DamageWidget;

public:
	virtual void BeginPlay() override;

public:
	void Hit(class ACharacter* InAttacker, const FHitData& InHitData, EPhysicalSurface InBodyPart, FHitResult SweepResult);
	void End_Hit() override;
	void Dead() override;
	void PrintDamage(class ACharacter* InAttacker, int InDamage, int x, int y, int distance);

};
