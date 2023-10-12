#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Monster/Actions/CMonsterActionStructures.h"
#include "CFireball.generated.h"

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API ACFireball : public AActor
{
	GENERATED_BODY()
	
public:	
	ACFireball();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* Projectile;

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Particle;

	UPROPERTY(EditAnywhere, Category="OnHit")
		class UParticleSystem* HitParticle;

	UPROPERTY(EditDefaultsOnly, Category="OnHit")
		class UMaterialInstanceConstant* HitDecal;

	UPROPERTY(EditDefaultsOnly, Category="OnHit")
		FPlayerHitData HitData;

public:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};