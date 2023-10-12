#include "Monster/Dragon/CDragon.h"
#include "Character/Player/CAnimInstance.h"
#include "Components/CMonsterBehaviorComponent.h"
#include "Particles/ParticleSystemComponent.h"

ACDragon::ACDragon()
{
	// Skeletal Mesh
	{
		FString path = "SkeletalMesh'/Game/Assets/UnkaDragon/Meshes/UnkaDragon/SK_Unka_Realistic.SK_Unka_Realistic'";
		ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(*path);

		GetMesh()->SetSkeletalMesh(skeletalMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	//Anim Instance
	{
		TSubclassOf<UCAnimInstance> animInstance;
		FString path = "AnimBlueprint'/Game/Monsters/Dragon/ABP_Dragon.ABP_Dragon_C'";
		animInstance = ConstructorHelpers::FClassFinder<UCAnimInstance>(*path).Class;
		GetMesh()->SetAnimClass(animInstance);
	}
}

void ACDragon::BeginPlay()
{
	Super::BeginPlay();

	BehaviorComponent->SetWaitMode();
}
