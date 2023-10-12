#pragma once

#include "CoreMinimal.h"
#include "Character/Player/CAnimInstance.h"
#include "Components/CEquipmentComponent.h"
#include "CAnimInstance_Player.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCAnimInstance_Player : public UCAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		EEquipmentType EquipmentType = EEquipmentType::Unarmed;

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
		void OnEquipmentTypeChanged(EEquipmentType InPrevType, EEquipmentType InNewType);

private:
	class UCEquipmentComponent* EquipmentComponent;
};
