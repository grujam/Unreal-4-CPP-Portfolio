#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Monster/Actions/CMonsterActionStructures.h"
#include "CBreath.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACBreath : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBreath();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere)
		class UNiagaraComponent* Effect;

	UPROPERTY(EditAnywhere, Category = "OnHit")
		class UParticleSystem* HitParticle;

	UPROPERTY(EditDefaultsOnly, Category = "OnHit")
		FPlayerHitData HitData;

public:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	TArray<class IIDamageable*> Hit;
};
