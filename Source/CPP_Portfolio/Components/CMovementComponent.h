#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "CMovementComponent.generated.h"

UENUM()
enum class ESpeed : uint8
{
	Walk = 0, Run, Max,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Sensitivity")
		float HorizontalSensitivity = 0.45;
	
	UPROPERTY(EditAnywhere, Category = "Sensitivity")
		float VerticalSensitivity = 0.45;

	UPROPERTY(EditAnywhere, Category = "Acceleration")
		float Acceleration = 500;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed[(int32)ESpeed::Max] = { 400, 600 };

public:
	FORCEINLINE bool IsMovable() const { return bCanMove; }
	FORCEINLINE void Move() { bCanMove = true;}
	FORCEINLINE void Stop() { bCanMove = false; }
	FORCEINLINE bool IsRunning() const { return bRunning; }

	FORCEINLINE float GetSpeed() const { return OwnerCharacter->GetVelocity().Size2D(); }

	FORCEINLINE bool IsCameraMovable() const { return bEnableCamera; }
	FORCEINLINE void EnableCamera() { bEnableCamera = true; }
	FORCEINLINE void DisableCamera() { bEnableCamera = false; }

public:
	void OnMoveForward(float InScale);
	void OnMoveSideWays(float InScale);
	void OnHorizontalLook(float InScale);
	void OnVerticalLook(float InScale);

	void OnDash();
	void OffDash();

public:
	void EnableControlRotation();
	void DisableControlRotation();

public:
	void ChangeSpeed(ESpeed InSpeed);

private:
	class ACharacter* OwnerCharacter;

private:
	bool bCanMove = true;
	bool bEnableCamera = true;
	bool bRunning = false;

	ESpeed NewSpeed = ESpeed::Walk;
	float speed = Speed[(int32)ESpeed::Walk];
};
