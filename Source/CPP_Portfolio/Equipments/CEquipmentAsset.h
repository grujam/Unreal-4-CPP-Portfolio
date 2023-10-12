#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CEquipmentStructures.h"
#include "CEquipmentAsset.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCEquipmentAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UCEquipmentAsset();

public:
	void BeginPlay(class ACharacter* InOwner, class UCEquipmentData** InEquipmentData);

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCEquip> EquipClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCActions> ActionClass;

	UPROPERTY(EditAnywhere)
		FEquipData EquipData;

	UPROPERTY(EditAnywhere)
		FEquipData UnequipData;

	UPROPERTY(EditAnywhere)
		TArray<FActionDataArray> ActionDataArrays;
};
