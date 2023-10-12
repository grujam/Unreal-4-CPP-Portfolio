#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipments/CEquipmentStructures.h"
#include "CHitComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCHitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCHitComponent();

public:
	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetHP() { return HP; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetMaxHP() { return MaxHP; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetHPPercent() { return HP / MaxHP; }

public:
	UPROPERTY(EditAnywhere, Category = "Resource")
		float MaxHP;

	UPROPERTY(EditAnywhere, Category = "Resource")
		float HP;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
		class ACharacter* OwnerCharacter;

public:
	UFUNCTION()
		void Hit(const FHitData& InHitData);

	UFUNCTION()
		virtual void End_Hit();

	UFUNCTION()
		virtual void Dead();
};
