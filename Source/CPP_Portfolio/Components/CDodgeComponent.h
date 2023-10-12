#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CEquipmentComponent.h"
#include "Monster/Actions/CMonsterActionStructures.h"
#include "CDodgeComponent.generated.h"

USTRUCT()
struct FDodgeData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		float StaminaCost = 20.0f;

public:
	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* Montages[(uint8)ESides::Max];
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCDodgeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCDodgeComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void Dodge();

	UFUNCTION()
		void End_Dodge();

public:
	UPROPERTY(EditAnywhere)
		TMap<EEquipmentType, FDodgeData> Dodges;

private:
	UPROPERTY()
		class ACharacter* OwnerCharacter;
};
