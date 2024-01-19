#include "Components/CIKComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UCIKComponent::UCIKComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCIKComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = Cast<ACharacter>(GetOwner());
}


void UCIKComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UCIKComponent::Trace(FName InSocketName,const float& InTraceDistance, float& OutDistance, FRotator& OutRotation)
{
	FVector socketLoc = Owner->GetMesh()->GetSocketLocation(InSocketName);

	float z = Owner->GetActorLocation().Z;
	FVector start = FVector(socketLoc.X, socketLoc.Y, z);

	z = start.Z - Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - InTraceDistance;
	FVector end = FVector(socketLoc.X, socketLoc.Y, z);

	TArray<AActor*> ignores;
	ignores.Add(Owner);
	
	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery1, true, ignores, DrawDebugTraceType, hitResult, true, FLinearColor::Red);

	OutDistance = 0;
	OutRotation = FRotator::ZeroRotator;

	if (hitResult.bBlockingHit == false)
		return;

	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	OutDistance = length - InTraceDistance;

	float roll = UKismetMathLibrary::DegAtan2(hitResult.Normal.Y, hitResult.Normal.Z);
	float pitch = -UKismetMathLibrary::DegAtan2(hitResult.Normal.X, hitResult.Normal.Z);
	OutRotation = FRotator(pitch, 0, roll);
}

