#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CMonsterActionStructures.generated.h"

UENUM()
enum class ESides : uint8
{
	Left, Right, Front, Back, Max
};

UENUM()
enum class EHitStrength : uint8
{
	Weak, Normal, Strong, KnockBack, Max
};

USTRUCT()
struct FPlayerHitData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Damage;

	UPROPERTY(EditAnywhere)
		EHitStrength HitStrength;

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
struct FPlayerHitMontage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UMatineeCameraShake> CameraShake;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* montages[(int32)ESides::Max];
};

USTRUCT()
struct FMonsterAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1;

	UPROPERTY(EditAnywhere)
		bool bFocus = false;

	UPROPERTY(EditAnywhere)
		FPlayerHitData PlayerHitData;

	void Action(class ACMonster* InMonster);
};

UCLASS()
class CPP_PORTFOLIO_API UCMonsterActionStructures : public UObject
{
	GENERATED_BODY()
	
};
