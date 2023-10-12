#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Components/CMonsterStateComponent.h"
#include "CAnimNotify_MEndState.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCAnimNotify_MEndState : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere)
		EMonsterStateType Type;
};
