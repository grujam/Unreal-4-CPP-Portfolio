#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayableCharacter.generated.h"

UCLASS(Abstract)
class CPP_PORTFOLIO_API ACPlayableCharacter
	: public ACharacter,
	  public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACPlayableCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		class UCMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere)
		uint8 TeamID = 1;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(TeamID); }
};
