#include "Equipments/CEquipment.h"
#include "Character/Interface/IDamageable.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Character.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

ACEquipment::ACEquipment()
{
	Root = this->CreateDefaultSubobject<USceneComponent>("Root");
	this->SetRootComponent(Root);
}

void ACEquipment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	TArray<USceneComponent*> children;
	Root->GetChildrenComponents(true, children);

	for(USceneComponent* child : children)
	{
		UShapeComponent* collider = Cast<UShapeComponent>(child);

		if(collider != nullptr)
		{
			Collisions.Add(collider);

			collider->OnComponentBeginOverlap.AddDynamic(this, &ACEquipment::OnComponentBeginOverlap);
			collider->OnComponentEndOverlap.AddDynamic(this, &ACEquipment::OnComponentEndOverlap);
		}
	}

	OffCollisions();
	Super::BeginPlay();
}

void ACEquipment::AttachToSocket(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, InSocketName);
}

void ACEquipment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OwnerCharacter == OtherActor)
		return;

	if (OnEquipmentBeginOverlap.IsBound())
		OnEquipmentBeginOverlap.Broadcast(OtherComp, OtherBodyIndex, OwnerCharacter, this, OtherActor, SweepResult);
}

void ACEquipment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OwnerCharacter == OtherActor)
		return;

	if (OnEquipmentEndOverlap.IsBound())
		OnEquipmentEndOverlap.Broadcast(OwnerCharacter, OtherActor);
}

void ACEquipment::OnCollisions()
{
	if (OnEquipmentOnCollision.IsBound())
		OnEquipmentOnCollision.Broadcast();

	for (UShapeComponent* collider : Collisions)
		collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACEquipment::OffCollisions()
{
	if (OnEquipmentOffCollision.IsBound())
		OnEquipmentOffCollision.Broadcast();

	for (UShapeComponent* collider : Collisions)
		collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

