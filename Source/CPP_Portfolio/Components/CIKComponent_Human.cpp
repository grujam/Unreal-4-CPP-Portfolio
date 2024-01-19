#include "Components/CIKComponent_Human.h"
#include "Kismet/KismetMathLibrary.h"

UCIKComponent_Human::UCIKComponent_Human()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCIKComponent_Human::BeginPlay()
{
	Super::BeginPlay();
}

void UCIKComponent_Human::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float leftDistance, rightDistance;
	FRotator leftRotation, rightRotation;

	Trace(LeftFootSocket, FeetTraceDistance, leftDistance, leftRotation);
	Trace(RightFootSocket, FeetTraceDistance, rightDistance, rightRotation);

	float offset = FMath::Min(leftDistance, rightDistance);

	IKFeetData.LeftDistance.X = FMath::FInterpTo(IKFeetData.LeftDistance.X, leftDistance-offset, DeltaTime, FeetInterpSpeed);
	IKFeetData.LeftRotation = FMath::RInterpTo(IKFeetData.LeftRotation, leftRotation, DeltaTime, FeetInterpSpeed);
	IKFeetData.RightDistance.X = FMath::FInterpTo(IKFeetData.RightDistance.X, -(rightDistance-offset), DeltaTime, FeetInterpSpeed);
	IKFeetData.RightRotation = FMath::RInterpTo(IKFeetData.RightRotation, rightRotation, DeltaTime, FeetInterpSpeed);
	IKFeetData.PelvisDistance.Z = FMath::FInterpTo(IKFeetData.PelvisDistance.Z, offset, DeltaTime, FeetInterpSpeed);
}
