#pragma once

#include "CoreMinimal.h"
#include "Components/CHitComponent.h"
#include "Monster/Actions/CMonsterActionStructures.h"
#include "CHitComponent_Player.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP_PORTFOLIO_API UCHitComponent_Player : public UCHitComponent
{
	GENERATED_BODY()

public:
	UCHitComponent_Player();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		TMap<EHitStrength, FPlayerHitMontage> Montages;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		class UAnimMontage* StandUpMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		class UAnimMontage* DownMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		TArray<class UAnimMontage*> DeadMontages;

public:
	virtual void BeginPlay() override;

public:
	FORCEINLINE void SetInvincibility(bool InValue) { bInvincible = InValue; }
	FORCEINLINE bool GetInvincibility() { return bInvincible; }

	FORCEINLINE class UAnimMontage* GetStandUpMontage() { return StandUpMontage; }
	FORCEINLINE class UAnimMontage* GetDownMontage() { return DownMontage; }

public:
	void Hit(const FPlayerHitData& InHitData, const FVector InAttackerLocation);
	void End_Hit() override;
	void Dead() override;
	
private:
	bool bInvincible = false;
};