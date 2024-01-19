#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CZipline.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACZipline : public AActor
{
	GENERATED_BODY()
	
public:	
	ACZipline();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		class USplineComponent* Spline;

	UPROPERTY(EditAnywhere)
		class UStaticMesh* Mesh;

private:
	UFUNCTION(BlueprintCallable)
		void CreateLine();

	UFUNCTION()
		void FollowLine(class ACharacter* InCharacter);

private:
	int Distance;
};
