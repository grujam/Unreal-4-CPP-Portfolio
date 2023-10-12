#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/Interface/IDamageable.h"
#include "CMonster.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACMonster
	: public ACharacter
	, public IIDamageable
{
	GENERATED_BODY()

public:
	ACMonster();

public:
	UPROPERTY(VisibleAnywhere)
		class UCMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere)
		class UCMonsterStateComponent* StateComponent;

	UPROPERTY(VisibleAnywhere)
		class UCMonsterActionComponent* ActionComponent;

	UPROPERTY(VisibleAnywhere)
		class UCHitComponent_Monster* HitComponent;

	UPROPERTY(VisibleAnywhere)
		class UCMonsterBehaviorComponent* BehaviorComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 2;

public:
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

public:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void TakeDamage(class ACharacter* InAttacker, const FHitData& InHitData, const EPhysicalSurface InBodyPart, FHitResult SweepResult) override;


};
