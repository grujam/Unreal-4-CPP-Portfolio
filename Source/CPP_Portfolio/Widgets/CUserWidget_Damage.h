#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Damage.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCUserWidget_Damage : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetDamage(int InDamage) { Damage = InDamage; }

	UFUNCTION(BlueprintCallable)
		int GetDamage();

private:
	int Damage = 0;
};
