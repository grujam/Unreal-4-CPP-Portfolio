#include "Monster/FieldMonster/Wolf/CWolf.h"
#include "Character/Player/CAnimInstance.h"

ACWolf::ACWolf()
{
	// Skeletal Mesh
	{
		FString path = "SkeletalMesh'/Game/Assets/AnimalVarietyPack/Wolf/Meshes/SK_Wolf.SK_Wolf'";
		ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(*path);

		GetMesh()->SetSkeletalMesh(skeletalMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	//Anim Instance
	{
		TSubclassOf<UCAnimInstance> animInstance;
		FString path = "AnimBlueprint'/Game/Monsters/Wolf/ABP_Wolf.ABP_Wolf_C'";
		animInstance = ConstructorHelpers::FClassFinder<UCAnimInstance>(*path).Class;
		GetMesh()->SetAnimClass(animInstance);
	}
}
