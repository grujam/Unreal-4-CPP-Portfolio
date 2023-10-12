#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMonsterCollision.generated.h"

class ACMonster;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FCollisionBeginOverlap, UPrimitiveComponent*, InOtherComp, int32, InOtherBodyIndex, ACMonster*, InAttacker, AActor*, InAttackActor, AActor*, InOther);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCollisionEndOverlap, ACMonster*, InAttacker, AActor*, InOther);

UCLASS()
class CPP_PORTFOLIO_API ACMonsterCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMonsterCollision();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
		TArray<class UShapeComponent*> Collisions;

protected:
	UPROPERTY(BlueprintReadOnly)
		class USceneComponent* Root;

	UPROPERTY(BlueprintReadOnly)
		class ACMonster* OwnerMonster;

public:
	UFUNCTION(BlueprintCallable)
		void OnCollisions();

	UFUNCTION(BlueprintCallable)
		void OnCollision(FString InCollisionName);

	UFUNCTION(BlueprintCallable)
		void OffCollisions();

	UFUNCTION(BlueprintCallable)
		void OffCollision(FString InCollisionName);

	UFUNCTION(BlueprintCallable)
		void AttachToComponent(class UShapeComponent* InCollider, FName InSocketName = NAME_None);

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FCollisionBeginOverlap OnCollisionBeginOverlap;
	FCollisionEndOverlap OnCollisionEndOverlap;

private:
	TArray<class IIDamageable*> HitCharacters;
};
