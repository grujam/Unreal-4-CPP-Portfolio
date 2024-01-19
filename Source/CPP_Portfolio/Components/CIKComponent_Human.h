#pragma once

#include "CoreMinimal.h"
#include "Components/CIKComponent.h"
#include "CIKComponent_Human.generated.h"

USTRUCT(BlueprintType)
struct FIKFeetData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Feet")
		FVector LeftDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Feet")
		FVector RightDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Feet")
		FVector PelvisDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Feet")
		FRotator LeftRotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Feet")
		FRotator RightRotation;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPP_PORTFOLIO_API UCIKComponent_Human : public UCIKComponent
{
	GENERATED_BODY()

public:
	UCIKComponent_Human();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE FIKFeetData GetIKFeetData() { return IKFeetData; }

public:
	UPROPERTY(EditAnywhere, Category = "Feet")
		FName LeftFootSocket = "Foot_L";

	UPROPERTY(EditAnywhere, Category = "Feet")
		FName RightFootSocket = "Foot_R";

	UPROPERTY(EditAnywhere, Category = "Feet")
		float FeetTraceDistance = 50;

	UPROPERTY(EditAnywhere, Category = "Feet")
		float FeetInterpSpeed = 50;

	UPROPERTY(EditAnywhere, Category = "Common")
		float IKOffset = 5;

private:
	FIKFeetData IKFeetData;

};
