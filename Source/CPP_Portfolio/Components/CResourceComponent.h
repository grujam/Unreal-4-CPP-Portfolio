#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCResourceComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, Category="Resource")
		float Stamina;

	UPROPERTY(EditAnywhere, Category="Resource")
		float MaxStamina;

	UPROPERTY(EditAnywhere, Category = "Resource")
		float StaminaRecoverRate = 0.1f;

private:
	UPROPERTY()
		class ACharacter* OwnerCharacter;

	UPROPERTY()
		class UCMovementComponent* MovementComponent;

public:
	void Run();
	void Walk();

public:
	FORCEINLINE float GetStamina() { return Stamina; }
	FORCEINLINE float GetMaxStamina() { return MaxStamina; }
	FORCEINLINE float GetStaminaPercent() { return Stamina / MaxStamina; }
	FORCEINLINE void SetRecoverStamina(bool InBool) { bRecoverStamina = InBool; }

public:
	void UseStamina(float InCost);

private:
	bool bRecoverStamina = true;
};
