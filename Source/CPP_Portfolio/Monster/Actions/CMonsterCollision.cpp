#include "Monster/Actions/CMonsterCollision.h"
#include "Components/ShapeComponent.h"
#include "Monster/CMonster.h"

ACMonsterCollision::ACMonsterCollision()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = this->CreateDefaultSubobject<USceneComponent>("Root");
	this->SetRootComponent(Root);
	
}


void ACMonsterCollision::BeginPlay()
{
	OwnerMonster = Cast<ACMonster>(GetOwner());

	TArray<USceneComponent*> children;
	Root->GetChildrenComponents(true, children);

	for(USceneComponent* child : children)
	{
		UShapeComponent* collider = Cast<UShapeComponent>(child);

		if (!!collider)
		{
			Collisions.Add(collider);
			collider->OnComponentBeginOverlap.AddDynamic(this, &ACMonsterCollision::OnComponentBeginOverlap);
			collider->OnComponentEndOverlap.AddDynamic(this, &ACMonsterCollision::OnComponentEndOverlap);
		}
	}

	Super::BeginPlay();

	OffCollisions();
}

void ACMonsterCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACMonsterCollision::OnCollisions()
{
	for (UShapeComponent* collider : Collisions)
	{
		collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ACMonsterCollision::OnCollision(FString InCollisionName)
{
	for(UShapeComponent* collider : Collisions)
	{
		FString name = collider->GetName();
		if (name == InCollisionName)
		{
			collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			return;
		}
	}
}

void ACMonsterCollision::OffCollisions()
{
	for (UShapeComponent* collider : Collisions)
	{
		collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACMonsterCollision::OffCollision(FString InCollisionName)
{
	for (UShapeComponent* collider : Collisions)
	{
		FString name = collider->GetName();
		if (name == InCollisionName)
		{
			collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			return;
		}
	}
}

void ACMonsterCollision::AttachToComponent(UShapeComponent* InCollider, FName InSocketName)
{
	InCollider->AttachToComponent(OwnerMonster->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, InSocketName);
}


void ACMonsterCollision::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OnCollisionBeginOverlap.IsBound())
		OnCollisionBeginOverlap.Broadcast(OtherComp, OtherBodyIndex, OwnerMonster, this, OtherActor);
}

void ACMonsterCollision::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OnCollisionEndOverlap.IsBound())
		OnCollisionEndOverlap.Broadcast(OwnerMonster, OtherActor);
}
