#pragma once

#include "CoreMinimal.h"
#include "Character/Player/CAnimInstance.h"
#include "CAnimInstance_Dragon.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCAnimInstance_Dragon : public UCAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		bool bFlying;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
