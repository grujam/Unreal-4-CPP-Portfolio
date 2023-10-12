#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMonsterBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EMonsterBehaviorType : uint8
{
	Wait = 0, Patrol, Dead, Approach, Attack, Hit, Rest, Sleep, Judge, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCMonsterBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMonsterBehaviorComponent();

private:
	UPROPERTY(EditAnywhere, Category = "Key")
		FName MonsterBehaviorTypeKey = "MonsterBehavior";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName TargetKey = "Target";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName PatrolLocationKey = "PatrolLocation";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName MeleeKey = "Melee";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName AttackIndexKey = "AttackIndex";

private:
	UPROPERTY(VisibleAnywhere)
		class UBlackboardComponent* Blackboard;

public:
	FORCEINLINE void SetBlackboard(UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

public:
	ACharacter* GetTarget();

public:
	bool IsWaitMode();
	bool IsPatrolMode();
	bool IsDeadMode();
	bool IsApproachMode();
	bool IsAttackMode();
	bool IsHitMode();
	bool IsRestMode();
	bool IsSleepMode();
	bool IsJudgeMode();

public:
	void SetWaitMode();
	void SetPatrolMode();
	void SetDeadMode();
	void SetApproachMode();
	void SetAttackMode();
	void SetHitMode();
	void SetRestMode();
	void SetSleepMode();
	void SetJudgeMode();

public:
	void SetPatrolLocation(FVector InPatrolLocation);
	FVector GetPatrolLocation();

	void SetMelee(bool InBool);
	bool GetMelee();

	void SetAttackIndex(int8 InIndex);
	int8 GetAttackIndex();

private:
	void ChangeMonsterBehaviorType(EMonsterBehaviorType InMonsterBehaviorType);

private:
	EMonsterBehaviorType GetMonsterBehaviorType();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	ACharacter* OwnerCharacter;
};
