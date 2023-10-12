#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMonsterActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCMonsterActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMonsterActionComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
		class UCMonsterActionData* MonsterActionData;

private:
	UPROPERTY(EditAnywhere)
		class UCMonsterActionAsset* MonsterActionAsset;

	UPROPERTY()
		class ACMonster* OwnerMonster;

	UPROPERTY()
		class UCMonsterStateComponent* MonsterStateComponent;

public:
	void Action(uint8 InIndex);
	class UCMonsterAction* GetAction();

public:
	TSubclassOf<AActor> GetSkillClass(FString InSkillName);
};
