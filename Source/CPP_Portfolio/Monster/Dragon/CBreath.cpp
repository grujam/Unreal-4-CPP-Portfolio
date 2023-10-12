#include "Monster/Dragon/CBreath.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/Player/CPlayer.h"
#include "NiagaraComponent.h"

ACBreath::ACBreath()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Effect = CreateDefaultSubobject<UNiagaraComponent>("Effect");
	Effect->SetupAttachment(Root);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Collider");
	Capsule->SetupAttachment(Effect);
}


void ACBreath::BeginPlay()
{
	Super::BeginPlay();
	
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACBreath::OnComponentBeginOverlap);
	SetLifeSpan(2.6);
}

void ACBreath::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IIDamageable* character = Cast<IIDamageable>(OtherActor);
	if (character == nullptr)
		return;

	for(IIDamageable* hit : Hit)
	{
		if (character == hit)
			return;
	}

	ACPlayer* player = Cast<ACPlayer>(character);
	//Player의 경우 다른 데미지 시스템
	if (player == nullptr)
		return;

	Hit.Add(player);
	player->TakeDamage(HitData, GetOwner()->GetActorLocation());
}
