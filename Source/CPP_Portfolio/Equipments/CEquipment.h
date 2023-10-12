#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentOnCollision);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentOffCollision);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FEquipmentBeginOverlap, UPrimitiveComponent*, InOtherComp, int32, InOtherBodyIndex, ACharacter*, InAttacker, AActor*, InAttackActor, AActor*, InOther, FHitResult, SweepResult);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEquipmentEndOverlap, ACharacter*, InAttacker, AActor*, InOther);

UCLASS()
class CPP_PORTFOLIO_API ACEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEquipment();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnBeginEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

public:
	UFUNCTION(BlueprintCallable, Category = "Attach")
		void AttachToSocket(FName InSocketName);

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void OnCollisions();
	void OffCollisions();

public:
	FEquipmentOnCollision OnEquipmentOnCollision;
	FEquipmentOffCollision OnEquipmentOffCollision;

	FEquipmentBeginOverlap OnEquipmentBeginOverlap;
	FEquipmentEndOverlap OnEquipmentEndOverlap;

protected:
	UPROPERTY(BlueprintReadOnly)
		class USceneComponent* Root;

	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		TArray<class UShapeComponent*> Collisions;

private:
	TArray<class IIDamageable*> Hitted;
};

