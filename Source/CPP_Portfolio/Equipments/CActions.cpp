#include "Equipments/CActions.h"
#include "Character/Interface/IDamageable.h"
#include "Character/Player/CPlayer.h"
#include "Components/CMovementComponent.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Utilities/CBodyMap.h"
#include "Kismet/KismetMathLibrary.h"

UCActions::UCActions()
{
	ActionType.Init(false, 7);
	Index.Init(0, 7);
}

void UCActions::BeginPlay(ACEquipment* InEquipment, UCEquip* InEquip, ACharacter* InOwner,
                          TArray<FActionDataArray>& InActionDataArray)
{
	OwnerCharacter = InOwner;
	World = OwnerCharacter->GetWorld();

	StateComponent = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));
	MovementComponent = Cast<UCMovementComponent>(OwnerCharacter->GetComponentByClass(UCMovementComponent::StaticClass()));

	ActionDataArray = InActionDataArray;
}

void UCActions::Action(EActionType InType)
{
	if (bEnableNext == true)
	{
		bEnableNext = false;
		NextActionType = InType;
		bNextAction = true;

		return;
	}

	if(StateComponent->IsIdleState())
	{
		//TODO: Dash Attack
		//if(MovementComponent->IsRunning())
		//{
		//	TArray<FActionData>& actionData = ActionDataArray[(int32)EActionType::Dash].ActionDatas;
		//	actionData[0].Action(OwnerCharacter);

		//	ActionType = actionData[0].NextActionable;
		//	index = actionData[0].NextActionIndex;

		//	return;
		//}
		StateComponent->SetActionState();

		TArray<FActionData> actionData = ActionDataArray[(int32)InType].ActionDatas;

		ActionType = actionData[0].NextActionable;
		Index = actionData[0].NextActionIndex;

		HitData = actionData[0].Hitdata;

		actionData[0].Action(OwnerCharacter);
		return;
	}
}

void UCActions::Begin_Action() 
{
	if (bNextAction == false)
		return;

	bNextAction = false;

	if (ActionType[int32(NextActionType)] == true)
	{
		TArray<FActionData> actionData = ActionDataArray[(int32)NextActionType].ActionDatas;
		uint8 idx = Index[(int32)NextActionType];
		if (idx < actionData.Num())
		{
			ActionType = actionData[idx].NextActionable;
			Index = actionData[idx].NextActionIndex;

			actionData[idx].Action(OwnerCharacter);
		}
	}
}

void UCActions::End_Action()
{
	StateComponent->SetIdleState();

	MovementComponent->Move();
	MovementComponent->EnableCamera();

	bNextAction = false;
}

void UCActions::OnEquipmentEndCollision()
{
	Hitted.Empty();
}

void UCActions::OnEquipmentBeginOverlap(UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex, ACharacter* InAttacker, AActor* InAttackActor, AActor* InOther, FHitResult SweepResult)
{
	IIDamageable* character = Cast<IIDamageable>(InOther);

	if (character == nullptr || InOtherBodyIndex == -1)
		return;

	for (IIDamageable* hitted : Hitted)
	{
		if (hitted == character)
			return;
	}
	
	USkeletalMeshComponent* comp = Cast<USkeletalMeshComponent>(InOtherComp);

	if (!!comp)
	{
		FBodyInstance* BodyInstance = comp->GetBodyInstance(comp->GetBoneName(InOtherBodyIndex));

		if (BodyInstance != nullptr)
		{
			UPhysicalMaterial* physmat = BodyInstance->GetSimplePhysicalMaterial();

			Hitted.AddUnique(character);

			const UEnum* enumProperty = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPhysicalSurface"), true);

			if(!!enumProperty)
			{
				FString str = CBodyMap::Map[physmat->GetName()];
				int32 index = enumProperty->GetIndexByNameString(str);
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, physmat->GetName());
				EPhysicalSurface type = EPhysicalSurface((uint8)index);

				character->TakeDamage(OwnerCharacter, HitData, type, SweepResult);
			}
		}
	}
}

void UCActions::OnEquipmentEndOverlap(ACharacter* InAttacker, AActor* InOther)
{

}
