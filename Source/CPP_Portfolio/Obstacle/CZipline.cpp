#include "Obstacle/CZipline.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "LoadingScreen.h"

ACZipline::ACZipline()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	Spline->SetupAttachment(Root);
}

void ACZipline::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CreateLine();
}

void ACZipline::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACZipline::CreateLine()
{
	int8 num = Spline->GetNumberOfSplinePoints() - 2;

	for (int8 i = 0; i < num + 1; ++i)
	{
		FVector StartLocation, EndLocation, StartTangent, EndTangent;

		Spline->GetLocationAndTangentAtSplinePoint(i, StartLocation, StartTangent, ESplineCoordinateSpace::Local);
		Spline->GetLocationAndTangentAtSplinePoint(i + 1, EndLocation, EndTangent, ESplineCoordinateSpace::Local);

		USplineMeshComponent* mesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		mesh->SetMobility(EComponentMobility::Movable);

		if (Mesh != nullptr)
			mesh->SetStaticMesh(Mesh);

		mesh->SetStartAndEnd(StartLocation, StartTangent, EndLocation, EndTangent);
		mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void ACZipline::FollowLine(ACharacter* InCharacter)
{

}
