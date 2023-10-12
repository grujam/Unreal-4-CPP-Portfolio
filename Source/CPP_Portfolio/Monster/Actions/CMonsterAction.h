#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Monster/Actions/CMonsterActionStructures.h"
#include "CMonsterAction.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCMonsterAction : public UObject
{
	GENERATED_BODY()
	
public:	
	UCMonsterAction();

public:
	void BeginPlay(class ACMonster* InMonster, TArray<FMonsterAction> InActions);

private:
	UPROPERTY()
		class ACMonster* OwnerMonster;

	UPROPERTY()
		class UCMonsterBehaviorComponent* MonsterBehaviorComponent;

	UPROPERTY()
		class UCMonsterStateComponent* MonsterStateComponent;


public:
	UFUNCTION()
		void Action(uint8 InIndex);

	UFUNCTION()
		void EndAction();

	UFUNCTION()
		void OnCollisionBeginOverlap(UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex, ACMonster* InAttacker, AActor* InAttackActor, AActor* InOther);

	UFUNCTION()
		void OnCollisionEndOverlap(ACMonster* InAttacker, AActor* InOther);

private:
	FPlayerHitData PlayerHitData;
	TArray<FMonsterAction> Actions;
};
