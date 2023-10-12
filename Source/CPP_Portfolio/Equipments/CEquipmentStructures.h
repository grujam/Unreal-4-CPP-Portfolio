#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CEquipmentStructures.generated.h"


USTRUCT()
struct FEquipData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bUseControlRotation = true;
};

UENUM()
enum class EActionType : uint8
{
	Left, Right, Double, ExtraLeft, ExtraRight, Extra, Dash, Max
};

USTRUCT()
struct FHitData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Damage;

	UPROPERTY(EditAnywhere)
		class USoundWave* Sound;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
		FVector EffectLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
		FVector EffectScale = FVector::OneVector;

public:
	void PlaySoundWave(class ACharacter* InOwner);
	void PlayEffect(UWorld* InWorld, const FVector& InLocation);
	void PlayEffect(UWorld* InWorld, const FVector& InLocation, const FRotator& InRotation);
};

USTRUCT()
struct FActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1;

	UPROPERTY(EditAnywhere)
		bool bCanMove = false;

	UPROPERTY(EditAnywhere)
		bool bFixedCamera = false;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
		FVector EffectLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
		FVector EffectScale = FVector::OneVector;

	UPROPERTY(EditAnywhere)
		TArray<bool> NextActionable;

	UPROPERTY(EditAnywhere)
		TArray<uint8> NextActionIndex;

	UPROPERTY(EditAnywhere)
		FHitData Hitdata;

	void Action(class ACharacter* InOwnerCharacter);
};

USTRUCT()
struct FActionDataArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EActionType ActionType;

	UPROPERTY(EditAnywhere)
		TArray<FActionData> ActionDatas;

};

USTRUCT()
struct FBodyDamage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		uint32 BreakDamage;

	UPROPERTY(EditAnywhere)
		uint8 BreakCount;

	UPROPERTY(EditAnywhere)
		uint32 DamageTaken = 0;
};

UCLASS()
class CPP_PORTFOLIO_API UCEquipmentStructures : public UObject
{
	GENERATED_BODY()

};