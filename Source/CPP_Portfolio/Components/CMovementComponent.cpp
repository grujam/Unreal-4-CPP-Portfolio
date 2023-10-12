#include "Components/CMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

UCMovementComponent::UCMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	speed = FMath::FInterpConstantTo(speed, Speed[(int32)NewSpeed], DeltaTime, Acceleration);
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = speed;
}


void UCMovementComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCMovementComponent::OnMoveForward(float InScale)
{
	if (!bCanMove)
		return;

	FRotator rotator = FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	OwnerCharacter->AddMovementInput(direction, InScale);
}

void UCMovementComponent::OnMoveSideWays(float InScale)
{
	if (!bCanMove)
		return;

	FRotator rotator = FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	OwnerCharacter->AddMovementInput(direction, InScale);
}

void UCMovementComponent::OnHorizontalLook(float InScale)
{
	if (!bEnableCamera)
		return;

	float InputScale = InScale * HorizontalSensitivity * 100 * GetWorld()->GetDeltaSeconds();
	OwnerCharacter->AddControllerYawInput(InputScale);
}

void UCMovementComponent::OnVerticalLook(float InScale)
{
	if (!bEnableCamera)
		return;

	float InputScale = InScale * VerticalSensitivity * 100 * GetWorld()->GetDeltaSeconds();
	OwnerCharacter->AddControllerPitchInput(InputScale);
}

void UCMovementComponent::OnDash()
{
	ChangeSpeed(ESpeed::Run);
	bRunning = true;
}

void UCMovementComponent::OffDash()
{
	ChangeSpeed(ESpeed::Walk);
	bRunning = false;
}

void UCMovementComponent::EnableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UCMovementComponent::DisableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void UCMovementComponent::ChangeSpeed(ESpeed InSpeed)
{
	NewSpeed = InSpeed;
}
