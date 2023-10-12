#include "Monster/Dragon/CFireball.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Player/CPlayer.h"

ACFireball::ACFireball()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	Projectile->ProjectileGravityScale = 0;
	Projectile->InitialSpeed = 1500;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	Capsule->SetupAttachment(Root);
	Capsule->SetCollisionProfileName("OverlapAll");

	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetupAttachment(Root);
}


void ACFireball::BeginPlay()
{
	Super::BeginPlay();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACFireball::OnComponentBeginOverlap);
}

void ACFireball::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this->GetOwner())
		return;

	ACPlayer* character = Cast<ACPlayer>(OtherActor);
	
	if (!!HitParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, this->GetActorLocation(), FRotator::ZeroRotator, FVector(2));
	}

	if (character == nullptr)
	{
		//TODO: Fireball Decal Spawn
		/*if (!!HitDecal)
		{
			GLog->Log("Decal");

			FRotator rotator = SweepResult.ImpactNormal.Rotation();

			UGameplayStatics::SpawnDecalAtLocation(OtherActor, HitDecal, FVector(1), this->GetActorLocation(), rotator, 10);
		}*/

		this->Destroy();
		return;
	}

	character->TakeDamage(HitData, this->GetActorLocation());
	this->Destroy();
}
